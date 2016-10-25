/*
 * Copyright (C) 2010 The OpenRcon Project.
 *
 * This file is part of OpenRcon.
 *
 * OpenRcon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenRcon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QTcpSocket>
#include <QHostAddress>
#include <QRegularExpression>

#include "FrostbiteConnection.h"
#include "FrostbiteRconPacket.h"
#include "FrostbiteCommandHandler.h"
#include "FrostbiteUtils.h"

FrostbiteConnection::FrostbiteConnection(QObject *parent) :
    Connection(parent),
    packetReadState(PacketReadingHeader),
    nextPacketSequence(0)
{
    qDebug() << "FrostbiteConnection created.";

    connect(socket, &QAbstractSocket::readyRead, this, &FrostbiteConnection::readyRead);
}

FrostbiteConnection::~FrostbiteConnection()
{

}

FrostbiteCommandHandler *FrostbiteConnection::getCommandHandler() const
{
    return commandHandler;
}

void FrostbiteConnection::setCommandHandler(FrostbiteCommandHandler *commandHandler)
{
    this->commandHandler = commandHandler;
}

void FrostbiteConnection::hostConnect(ServerEntry *serverEntry)
{
    if (!socket->isOpen()) {
        clear();
    }

    Connection::hostConnect(serverEntry);
}

void FrostbiteConnection::sendCommand(const QString &command)
{
    if (!command.isEmpty()) {
        FrostbiteRconPacket packet(FrostbiteRconPacket::ServerOrigin, FrostbiteRconPacket::Request, nextPacketSequence);
        QStringList wordList;
        wordList = command.split(QRegularExpression(" +(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)"));
        wordList.replaceInStrings("\"", "", Qt::CaseSensitive);

        for (QString word : wordList) {
            packet.packWord(FrostbiteRconWord(word.toLatin1().constData()));
        }

        sendPacket(packet);
        nextPacketSequence++;
    }
}

void FrostbiteConnection::clear()
{
    packetSendQueue.clear();
    packetReadState = PacketReadingHeader;
    nextPacketSequence = 0;
}

void FrostbiteConnection::sendPacket(const FrostbiteRconPacket &packet, bool response)
{
    QDataStream out(socket);
    out << packet;

    if (!response) {
        packetSendQueue.push_back(packet);
    }
}

void FrostbiteConnection::handlePacket(const FrostbiteRconPacket &packet)
{
    if (packet.isResponse()) {
        QVector<FrostbiteRconPacket>::iterator it;

        for (it = packetSendQueue.begin(); it < packetSendQueue.end(); it++) {
            if (it->getSequenceNum() == packet.getSequenceNum()) {
                break;
            }
        }

        if (it != packetSendQueue.end()) {
            const FrostbiteRconPacket& lastSentPacket = *it;

            if (lastSentPacket.getSequenceNum() == packet.getSequenceNum()) {
                if (lastSentPacket.getWordCount() > 0) {
                    QString request = lastSentPacket.getWord(0).getContent();

                    if (packet.getWordCount() > 0) {
                        QString messages = request + " ";

                        for (unsigned int i = 1; i < lastSentPacket.getWordCount(); i++) {
                            messages += lastSentPacket.getWord(i).getContent();
                            messages += " ";
                        }

                        responseDataSent(messages);
                        qDebug() << messages;

                        QString messager;
                        unsigned int packetWordCount = packet.getWordCount();

                        for (unsigned int i = 0; i < packetWordCount; i++) {
                            messager += packet.getWord(i).getContent();
                            messager += " ";
                        }

                        responseDataReceived(messager);
                        qDebug() << messager;

                        commandHandler->parse(request, packet, lastSentPacket);
                    }
                }
            }

            // BIG MISTAKE HERE: packetSendQueue.erase(it);
            for (it = packetSendQueue.begin(); it < packetSendQueue.end(); it++) {
                if (it->getSequenceNum() == packet.getSequenceNum()) {
                    packetSendQueue.erase(it);
                    break;
                }
            }
        }
    } else if (packet.getWordCount() > 0) {
        QString request = packet.getWord(0).getContent();
        QString message;

        for (unsigned int i = 0; i < packet.getWordCount(); i++) {
            message += packet.getWord(i).getContent();
            message += " ";
        }

        responseDataSent(message);
        commandHandler->parse(request, packet, FrostbiteRconPacket());
    }
}

void FrostbiteConnection::readyRead()
{
    bool exit = false;

    while (!exit) {
        switch (packetReadState) {
        case PacketReadingHeader:
            if (socket->bytesAvailable() >= MIN_PACKET_SIZE) {
                if (socket->read(lastHeader, MIN_PACKET_SIZE) != MIN_PACKET_SIZE) {
                    exit = true;

                    qDebug() << tr("Error while reading header.");
                    break;
                }
            } else {
                exit = true;
                break;
            }
        case PacketReadingData:
            QDataStream hdrstream(QByteArray(lastHeader, MIN_PACKET_SIZE));
            hdrstream.setByteOrder(QDataStream::LittleEndian);

            unsigned int sequence, length, words;
            hdrstream >> sequence;
            hdrstream >> length;
            hdrstream >> words;

            if (socket->bytesAvailable() >= length - MIN_PACKET_SIZE) {
                if (length >= MIN_PACKET_SIZE) {
                    char* data = new char[length];
                    memcpy(data, lastHeader, MIN_PACKET_SIZE);

                    if (socket->read(data + MIN_PACKET_SIZE, length - MIN_PACKET_SIZE) == length - MIN_PACKET_SIZE) {
                        QDataStream pstream(QByteArray(data, length));
                        FrostbiteRconPacket packet;
                        pstream >> packet;
                        handlePacket(packet);
                    } else {
                        qDebug() << tr("Error while reading data.");
                    }

                    delete[] data;
                } else {
                    qDebug() << tr("Malformed packet, ignoring...");
                }

                packetReadState = PacketReadingHeader;
            } else {
                packetReadState = PacketReadingData;
                exit = true;
            }

            break;
        }
    }
}
