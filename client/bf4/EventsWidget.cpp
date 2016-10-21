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

#include <QDateTime>
#include <QHostAddress>

#include "EventsWidget.h"
#include "ui_EventsWidget.h"
#include "FrostbiteConnection.h"
#include "BF4CommandHandler.h"
#include "TeamEntry.h"
#include "LevelEntry.h"
#include "BF4LevelDictionary.h"
#include "BF4GameModeEntry.h"
#include "FrostbiteUtils.h"

EventsWidget::EventsWidget(FrostbiteConnection *connection, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventsWidget),
    connection(connection),
    commandHandler(dynamic_cast<BF4CommandHandler *>(connection->getCommandHandler()))
{
    ui->setupUi(this);

    /* Connection */
    connect(connection, &FrostbiteConnection::onConnected, this, &EventsWidget::onConnected);
    connect(connection, &FrostbiteConnection::onDisconnected, this, &EventsWidget::onDisconnected);

    /* Events */
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerAuthenticatedEvent,       this, &EventsWidget::onPlayerAuthenticatedEvent);
    connect(commandHandler, &BF4CommandHandler::onPlayerDisconnectEvent,                 this, &EventsWidget::onPlayerDisconnectEvent);
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerJoinEvent,                this, &EventsWidget::onPlayerJoinEvent);
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerLeaveEvent,               this, &EventsWidget::onPlayerLeaveEvent);
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerSpawnEvent,               this, &EventsWidget::onPlayerSpawnEvent);
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerKillEvent,                this, &EventsWidget::onPlayerKillEvent);
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerChatEvent,                this, &EventsWidget::onPlayerChatEvent);
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerSquadChangeEvent,         this, &EventsWidget::onPlayerSquadChangeEvent);
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerTeamChangeEvent,          this, &EventsWidget::onPlayerTeamChangeEvent);
    connect(commandHandler, &BF4CommandHandler::onServerMaxPlayerCountChangeEvent,       this, &EventsWidget::onServerMaxPlayerCountChangeEvent);
    connect(commandHandler, &BF4CommandHandler::onServerLevelLoadedEvent,                this, &EventsWidget::onServerLevelLoadedEvent);
    connect(commandHandler, &Frostbite2CommandHandler::onServerRoundOverEvent,           this, &EventsWidget::onServerRoundOverEvent);
    connect(commandHandler, &Frostbite2CommandHandler::onServerRoundOverPlayersEvent,    this, &EventsWidget::onServerRoundOverPlayersEvent);
    connect(commandHandler, &Frostbite2CommandHandler::onServerRoundOverTeamScoresEvent, this, &EventsWidget::onServerRoundOverTeamScoresEvent);

    /* Commands */
    // Misc
    connect(commandHandler, static_cast<void (FrostbiteCommandHandler::*)(bool)>(&FrostbiteCommandHandler::onLoginHashedCommand), this, &EventsWidget::onLoginHashedCommand);
}

EventsWidget::~EventsWidget()
{
    delete ui;
}

void EventsWidget::logEvent(const QString &event, const QString &message)
{
    int row = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss")));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(event));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(message));
    ui->tableWidget->resizeColumnsToContents();
}

/* Connection */
void EventsWidget::onConnected(QAbstractSocket *socket)
{
    logEvent("Connected", tr("Connected to %1:%2.").arg(socket->peerAddress().toString()).arg(socket->peerPort()));
}

void EventsWidget::onDisconnected(QAbstractSocket *socket)
{
    Q_UNUSED(socket);

    logEvent("Disconnected", tr("Disconnected."));
}

/* Events */
void EventsWidget::onPlayerAuthenticatedEvent(const QString &player)
{
    logEvent("PlayerAuthenticated", tr("Player %1 authenticated.").arg(player));
}

void EventsWidget::onPlayerDisconnectEvent(const QString &player)
{
    logEvent("PlayerDisconnect", tr("Player %1 disconnected.").arg(player));
}

void EventsWidget::onPlayerJoinEvent(const QString &player, const QString &guid)
{
    logEvent("PlayerJoin", tr("Player %1 joined the game (GUID: %2).").arg(player, guid));
}

void EventsWidget::onPlayerLeaveEvent(const QString &player, const QString &info)
{
    Q_UNUSED(info);

    logEvent("PlayerLeave", tr("Player %1 left the game.").arg(player)); // TODO: Impelment score stuffs here?
}

void EventsWidget::onPlayerSpawnEvent(const QString &player, int teamId)
{
    logEvent("PlayerSpawn", tr("Player %1 spawned, and is on team %2.").arg(player).arg(BF4LevelDictionary::getTeam(teamId - 1).getName()));
}

void EventsWidget::onPlayerKillEvent(const QString &killer, const QString &victim, const QString &weapon, bool headshot)
{
    QString message;

    if (killer != victim) {
        if (headshot) {
            message = tr("Player %1 headshoted player %2 using %3.").arg(killer).arg(victim).arg(weapon);
        } else {
            message = tr("Player %1 killed player %2 with %3.").arg(killer).arg(victim).arg(weapon);
        }
    } else {
        message = tr("Player %1 commited sucide using %2.").arg(killer).arg(weapon);
    }

    logEvent("PlayerKill", message);
}

void EventsWidget::onPlayerChatEvent(const QString &sender, const QString &message, const QString &target)
{
    Q_UNUSED(target);

    logEvent("PlayerChat", QString("%1: %2").arg(sender).arg(message));
}

void EventsWidget::onPlayerSquadChangeEvent(const QString &player, int teamId, int squadId)
{
    Q_UNUSED(teamId);

    if (squadId != 0) {
        logEvent("PlayerSquadChange", tr("Player %1 changed squad to %2.").arg(player).arg(FrostbiteUtils::getSquadName(squadId)));
    }
}

void EventsWidget::onPlayerTeamChangeEvent(const QString &player, int teamId, int squadId)
{
    Q_UNUSED(squadId);

    logEvent("PlayerTeamChange", tr("Player %1 changed team to %2.").arg(player).arg(teamId));
}

void EventsWidget::onServerMaxPlayerCountChangeEvent()
{

}

void EventsWidget::onServerLevelLoadedEvent(const QString &levelName, const QString &gameModeName, int roundsPlayed, int roundsTotal)
{
    Q_UNUSED(roundsPlayed);
    Q_UNUSED(roundsTotal);

    LevelEntry level = BF4LevelDictionary::getLevel(levelName);
    GameModeEntry gameMode = BF4LevelDictionary::getGameMode(gameModeName);

    logEvent("ServerLevelLoaded", tr("Loading level %1 with gamemode %2.").arg(level.getName()).arg(gameMode.getName()));
}

void EventsWidget::onServerRoundOverEvent(int winningTeamId)
{
    logEvent("ServerRoundOver", tr("The round has just ended, and %1 won.").arg(winningTeamId));
}

void EventsWidget::onServerRoundOverPlayersEvent(const QString &playerInfo)
{
    logEvent("ServerRoundOverPlayers", tr("The round has just ended, and %1 is the final detailed player stats.").arg(playerInfo)); // TODO: Check what this actually outputs.
}

void EventsWidget::onServerRoundOverTeamScoresEvent(const QString &teamScores)
{
    logEvent("ServerRoundOverTeamScores", tr("The round has just ended, and %1 is the final ticket/kill/life count for each team.").arg(teamScores));
}

/* Commands */
void EventsWidget::onLoginHashedCommand(bool auth)
{
    if (auth) {
        commandHandler->sendAdminEventsEnabledCommand(true);
    }
}
