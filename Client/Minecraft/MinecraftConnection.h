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

#ifndef MINECRAFTCONNECTION_H
#define MINECRAFTCONNECTION_H

#include <QObject>

#include "Connection.h"
#include "MinecraftCommandHandler.h"

#define RCON_LOGIN 3
#define RCON_COMMAND 2

class MinecraftConnection : public Connection
{
    Q_OBJECT

public:
    explicit MinecraftConnection(QObject *parent = 0);
    ~MinecraftConnection();

    void sendPacket(const int &id, const int &type, const char* payload);
    void sendCommand(const QString &command);

private:
    MinecraftCommandHandler *commandHandler;

    void handlePacket(const int &type, const QString& command);

private slots:
    void readyRead();

signals:
    void onAuthenticated(bool auth);
    void onPacket(const QString &packet);

};

#endif // BFBC2CONNECTION_H
