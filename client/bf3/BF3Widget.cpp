/*
 * Copyright (C) 2014 The OpenRcon Project.
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

#include <QMessageBox>

#include "BF3Widget.h"
#include "ui_BF3Widget.h"
#include "BF3CommandHandler.h"
#include "PlayerInfo.h"
#include "PlayerSubset.h"
#include "TeamEntry.h"
#include "BF3LevelDictionary.h"
#include "FrostbiteUtils.h"

#include "ChatWidget.h"
#include "ReservedSlotsWidget.h"
#include "ConsoleWidget.h"

BF3Widget::BF3Widget(ServerEntry *serverEntry) : BF3(serverEntry), ui(new Ui::BF3Widget)
{
    ui->setupUi(this);

    chatWidget = new ChatWidget(m_connection, this);
    reservedSlotsWidget = new ReservedSlotsWidget(m_connection, this);
    consoleWidget = new ConsoleWidget(m_connection, this);

    ui->tabWidget->addTab(chatWidget, tr("Chat"));
    ui->tabWidget->addTab(reservedSlotsWidget, tr("Reserved Slots"));
    ui->tabWidget->addTab(consoleWidget, QIcon(":/icons/console.png"), tr("Console"));

    /* Connection */
    connect(m_connection, &Connection::onConnected,    this, &BF3Widget::onConnected);
    connect(m_connection, &Connection::onDisconnected, this, &BF3Widget::onDisconnected);

    /* Commands */
    // Misc
    connect(m_commandHandler, static_cast<void (FrostbiteCommandHandler::*)(bool)>(&FrostbiteCommandHandler::onLoginHashedCommand), this, &BF3Widget::onLoginHashedCommand);

    /* User Interface */
}

BF3Widget::~BF3Widget()
{
    delete ui;
}

void BF3Widget::setAuthenticated(bool authenticated)
{
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(chatWidget), authenticated);
//    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_op), authenticated);
//    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_ml), authenticated);
//    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_bl), authenticated);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(reservedSlotsWidget), authenticated);

    startupCommands(authenticated);
}

void BF3Widget::startupCommands(bool authenticated)
{
    // Misc
    m_commandHandler->sendVersionCommand();
    m_commandHandler->sendServerInfoCommand();

    if (authenticated) {
        m_commandHandler->sendAdminEventsEnabledCommand(true);

        // Admins

        // Banning

        // Maplist

        // Player

        // Punkbuster

        // Squad

        // Variables
    } else {
        m_commandHandler->sendListPlayersCommand(PlayerSubset::All);
    }
}

/* Connection */
void BF3Widget::onConnected()
{
    setAuthenticated(false);

//    logEvent("Connected", tr("Connected to %1:%2.").arg(con->tcpSocket->peerAddress().toString()).arg(con->tcpSocket->peerPort()));
}

void BF3Widget::onDisconnected()
{
//    logEvent("Disconnected", tr("Disconnected."));
}

/* Events */

/* Commands */

// Misc
void BF3Widget::onLoginHashedCommand(bool auth)
{
    if (auth) {
        // Call commands on startup.
        setAuthenticated(true);
    } else {
        int ret = QMessageBox::warning(0, tr("Error"), "Wrong password, make sure you typed in the right password and try again.");

        if (ret) {
            m_connection->hostDisconnect();
        }
    }
}

void BF3Widget::onListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset)
{
    listPlayers(playerList, playerSubset);
}

// Admin
void BF3Widget::onAdminListPlayersCommand(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset)
{
    listPlayers(playerList, playerSubset);
}

// Banning

// FairFight

// Maplist

// Player

// Punkbuster

// Reserved Slots

// Spectator list

// Squad

// Variables

QIcon BF3Widget::getRankIcon(int rank)
{
    return QIcon(QString(":/bf3/ranks/rank_%1.png").arg(rank));
}

/* User Interface */

// Players
void BF3Widget::updatePlayerList()
{
    if (isAuthenticated()) {
//        commandHandler->sendAdminListPlayersCommand(All);
    } else {
        m_commandHandler->sendListPlayersCommand(PlayerSubset::All);
    }
}

void BF3Widget::listPlayers(const QList<PlayerInfo> &playerList, const PlayerSubset &playerSubset)
{
    if (playerSubset == PlayerSubset::All) {
        ui->treeWidget_pl_players->clear();

        QList<QTreeWidgetItem *> playerItems;
        QSet<int> teamIds;

        for (PlayerInfo player : playerList) {
            QTreeWidgetItem *playerItem = new QTreeWidgetItem();
            playerItem->setIcon(0, getRankIcon(player.rank));
            playerItem->setText(0, player.name);
            playerItem->setText(1, FrostbiteUtils::getSquadName(player.squadId));
            playerItem->setText(2, QString::number(player.kills));
            playerItem->setText(3, QString::number(player.deaths));
            playerItem->setText(4, QString::number(player.score));
            playerItem->setText(5, QString::number(player.ping));
            playerItem->setText(6, player.guid);
            playerItem->setData(0, Qt::UserRole, player.teamId);

            // Add player item and team id to lists.
            playerItems.append(playerItem);
            teamIds.insert(player.teamId);
        }

        for (int teamId : teamIds) {
            if (teamId > 0) { // Don't list team with id 0, as this is the neutrual team.
                QTreeWidgetItem *teamItem = new QTreeWidgetItem(ui->treeWidget_pl_players);
                teamItem->setText(0, BF3LevelDictionary::getTeam(teamId - 1).name);

                foreach (QTreeWidgetItem *playerItem, playerItems) {
                    if (teamId == playerItem->data(0, Qt::UserRole)) {
                        teamItem->addChild(playerItem);
                    }
                }
            }
        }

        // Expand all player rows
        ui->treeWidget_pl_players->expandAll();

        // Sort players based on their score.
        ui->treeWidget_pl_players->sortItems(4, Qt::AscendingOrder);

        // Resize columns so that they fits the content.
        for (int i = 0; i < ui->treeWidget_pl_players->columnCount(); i++) {
            ui->treeWidget_pl_players->resizeColumnToContents(i);
        }
    }
}
