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
#include <QTreeWidgetItem>
#include <QToolTip>

#include <QSpinBox>

#include "FrostbiteUtils.h"
#include "Time.h"

#include "BF4Widget.h"
#include "ui_BF4Widget.h"
#include "BF4LevelDictionary.h"
#include "BF4CommandHandler.h"

#include "PlayerListWidget.h"
#include "ChatWidget.h"
#include "MapListWidget.h"
#include "ReservedSlotsWidget.h"
#include "SpectatorSlotsWidget.h"
#include "ConsoleWidget.h"

BF4Widget::BF4Widget(ServerEntry *serverEntry) : BF4(serverEntry), ui(new Ui::BF4Widget)
{
    ui->setupUi(this);

    /* User Inferface */

    // ServerInfo
    timerServerInfoRoundTime = new QTimer(this);
    connect(timerServerInfoRoundTime, &QTimer::timeout, this, &BF4Widget::updateRoundTime);
    timerServerInfoRoundTime->start(1000);

    timerServerInfoUpTime = new QTimer(this);
    connect(timerServerInfoUpTime, &QTimer::timeout, this, &BF4Widget::updateUpTime);
    timerServerInfoUpTime->start(1000);

    // Banlist
    menu_bl_banList = new QMenu(ui->tableWidget_bl_banList);
    action_bl_banList_remove = new QAction(tr("Remove"), menu_bl_banList);

    menu_bl_banList->addAction(action_bl_banList_remove);

    QStringList commandList;
    commandList.append("login.plainText");
    commandList.append("login.hashed");
    commandList.append("serverInfo");
    commandList.append("logout");
    commandList.append("quit");
    commandList.append("version");
    commandList.append("currentLevel");
    commandList.append("listPlayers");
    commandList.append("admin.eventsEnabled");
    commandList.append("admin.help");
    commandList.append("admin.kickPlayer");
    commandList.append("admin.killPlayer");
    commandList.append("admin.listPlayers");
    commandList.append("admin.movePlayer");
    commandList.append("admin.password");
    commandList.append("admin.say");
    commandList.append("admin.shutDown");
    commandList.append("admin.yell");
    commandList.append("banList.add");
    commandList.append("banList.clear");
    commandList.append("banList.list");
    commandList.append("banList.load");
    commandList.append("banList.remove");
    commandList.append("banList.save");
    commandList.append("fairFight.activate");
    commandList.append("fairfight.deactivate");
    commandList.append("fairFight.isActive");
    commandList.append("mapList.add");
    commandList.append("mapList.availableMaps");
    commandList.append("mapList.clear");
    commandList.append("mapList.endRound");
    commandList.append("mapList.getMapIndices");
    commandList.append("mapList.getRounds");
    commandList.append("mapList.list");
    commandList.append("mapList.load");
    commandList.append("mapList.remove");
    commandList.append("mapList.restartRound");
    commandList.append("mapList.runNextRound");
    commandList.append("mapList.save");
    commandList.append("mapList.setNextMapIndex");
    commandList.append("player.idleDuration");
    commandList.append("player.isAlive");
    commandList.append("player.ping");
    commandList.append("punkBuster.activate");
    commandList.append("punkBuster.isActive");
    commandList.append("punkBuster.pb_sv_command");
    commandList.append("reservedSlotsList.add");
    commandList.append("reservedSlotsList.aggressiveJoin");
    commandList.append("reservedSlotsList.clear");
    commandList.append("reservedSlotsList.list");
    commandList.append("reservedSlotsList.load");
    commandList.append("reservedSlotsList.remove");
    commandList.append("reservedSlotsList.save");
    commandList.append("spectatorList.add");
    commandList.append("spectatorList.clear");
    commandList.append("spectatorList.list");
    commandList.append("spectatorList.remove");
    commandList.append("spectatorList.save");
    commandList.append("squad.leader");
    commandList.append("squad.listActive");
    commandList.append("squad.listPlayers");
    commandList.append("squad.private");
    commandList.append("vars.3dSpotting");
    commandList.append("vars.3pCam");
    commandList.append("vars.alwaysAllowSpectators");
    commandList.append("vars.autoBalance");
    commandList.append("vars.bulletDamage");
    commandList.append("vars.commander");
    commandList.append("vars.forceReloadWholeMags");
    commandList.append("vars.friendlyFire");
    commandList.append("vars.gameModeCounter");
    commandList.append("vars.gamePassword");
    commandList.append("vars.hitIndicatorsEnabled");
    commandList.append("vars.hud");
    commandList.append("vars.idleBanRounds");
    commandList.append("vars.idleTimeout");
    commandList.append("vars.killCam");
    commandList.append("vars.maxPlayers");
    commandList.append("vars.maxSpectators");
    commandList.append("vars.miniMap");
    commandList.append("vars.miniMapSpotting");
    commandList.append("vars.mpExperience");
    commandList.append("vars.nameTag");
    commandList.append("vars.onlySquadLeaderSpawn");
    commandList.append("vars.playerRespawnTime");
    commandList.append("vars.preset");
    commandList.append("vars.regenerateHealth");
    commandList.append("vars.roundLockdownCountdown");
    commandList.append("vars.roundRestartPlayerCount");
    commandList.append("vars.roundStartPlayerCount");
    commandList.append("vars.roundTimeLimit");
    commandList.append("vars.roundWarmupTimeout");
    commandList.append("vars.serverDescription");
    commandList.append("vars.serverMessage");
    commandList.append("vars.serverName");
    commandList.append("vars.serverType");
    commandList.append("vars.soldierHealth");
    commandList.append("vars.teamFactionOverride");
    commandList.append("vars.teamKillCountForKick");
    commandList.append("vars.teamKillKickForBan");
    commandList.append("vars.teamKillValueDecreasePerSecond");
    commandList.append("vars.teamKillValueForKick");
    commandList.append("vars.teamKillValueIncrease");
    commandList.append("vars.unlockMode");
    commandList.append("vars.vehicleSpawnAllowed");
    commandList.append("vars.vehicleSpawnDelay");

    // Create tabs from widgets.
    playerListWidget = new PlayerListWidget(con, this);
    chatWidget = new ChatWidget(con, this);
    mapListWidget = new MapListWidget(con, this);
    reservedSlotsWidget = new ReservedSlotsWidget(con, this);
    spectatorSlotsWidget = new SpectatorSlotsWidget(con, this);
    consoleWidget = new ConsoleWidget(con, commandList, this);

    ui->tabWidget->addTab(playerListWidget, tr("Players"));
    ui->tabWidget->addTab(chatWidget, tr("Chat"));
    ui->tabWidget->addTab(mapListWidget, tr("Maplist"));
    ui->tabWidget->addTab(reservedSlotsWidget, tr("Reserved Slots"));
    ui->tabWidget->addTab(spectatorSlotsWidget, tr("Spectator Slots"));
    ui->tabWidget->addTab(consoleWidget, QIcon(":/icons/console.png"), tr("Console"));

    /* Connection */
    connect(con, SIGNAL(onConnected()), this, SLOT(onConnected()));
    connect(con, SIGNAL(onDisconnected()), this, SLOT(onDisconnected()));

    /* Events */ 
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerAuthenticatedEvent,       this, &BF4Widget::onPlayerAuthenticatedEvent);
    connect(commandHandler, &BF4CommandHandler::onPlayerDisconnectEvent,                 this, &BF4Widget::onPlayerDisconnectEvent);
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerJoinEvent,                this, &BF4Widget::onPlayerJoinEvent);
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerLeaveEvent,               this, &BF4Widget::onPlayerLeaveEvent);
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerSpawnEvent,               this, &BF4Widget::onPlayerSpawnEvent);
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerKillEvent,                this, &BF4Widget::onPlayerKillEvent);
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerChatEvent,                this, &BF4Widget::onPlayerChatEvent);
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerSquadChangeEvent,         this, &BF4Widget::onPlayerSquadChangeEvent);
    connect(commandHandler, &Frostbite2CommandHandler::onPlayerTeamChangeEvent,          this, &BF4Widget::onPlayerTeamChangeEvent);
    connect(commandHandler, &BF4CommandHandler::onServerMaxPlayerCountChangeEvent,       this, &BF4Widget::onServerMaxPlayerCountChangeEvent);
    connect(commandHandler, &BF4CommandHandler::onServerLevelLoadedEvent,                this, &BF4Widget::onServerLevelLoadedEvent);
    connect(commandHandler, &Frostbite2CommandHandler::onServerRoundOverEvent,           this, &BF4Widget::onServerRoundOverEvent);
    connect(commandHandler, &Frostbite2CommandHandler::onServerRoundOverPlayersEvent,    this, &BF4Widget::onServerRoundOverPlayersEvent);
    connect(commandHandler, &Frostbite2CommandHandler::onServerRoundOverTeamScoresEvent, this, &BF4Widget::onServerRoundOverTeamScoresEvent);

    /* Commands */
    // Misc
    connect(commandHandler, static_cast<void (FrostbiteCommandHandler::*)(bool)>(&FrostbiteCommandHandler::onLoginHashedCommand), this, &BF4Widget::onLoginHashedCommand);
    connect(commandHandler, &FrostbiteCommandHandler::onVersionCommand,                                                           this, &BF4Widget::onVersionCommand);
    connect(commandHandler, &BF4CommandHandler::onServerInfoCommand,                                                              this, &BF4Widget::onServerInfoCommand);

    // Admin
    connect(commandHandler, &BF4CommandHandler::onAdminPasswordCommand,               this, &BF4Widget::onAdminPasswordCommand);

    // BanList
    connect(commandHandler, &BF4CommandHandler::onBanListListCommand,                 this, &BF4Widget::onBanListListCommand);

    // FairFight
    connect(commandHandler, &BF4CommandHandler::onFairFightIsActiveCommand,           this, &BF4Widget::onFairFightIsActiveCommand);

    // Player

    // Punkbuster
    connect(commandHandler, &BF4CommandHandler::onPunkBusterIsActiveCommand,          this, &BF4Widget::onPunkBusterIsActiveCommand);

    // Squad

    // Variables  
    connect(commandHandler, &BF4CommandHandler::onVars3dSpottingCommand,              this, &BF4Widget::onVars3dSpottingCommand);
    connect(commandHandler, &BF4CommandHandler::onVars3pCamCommand,                   this, &BF4Widget::onVars3pCamCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsAlwaysAllowSpectatorsCommand,   this, &BF4Widget::onVarsAlwaysAllowSpectatorsCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsAutoBalanceCommand,             this, &BF4Widget::onVarsAutoBalanceCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsBulletDamageCommand,            this, &BF4Widget::onVarsBulletDamageCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsCommanderCommand,               this, &BF4Widget::onVarsCommanderCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsForceReloadWholeMagsCommand,    this, &BF4Widget::onVarsForceReloadWholeMagsCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsFriendlyFireCommand,            this, &BF4Widget::onVarsFriendlyFireCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsGameModeCounterCommand,         this, &BF4Widget::onVarsGameModeCounterCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsGamePasswordCommand,            this, &BF4Widget::onVarsGamePasswordCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsHitIndicatorsEnabledCommand,    this, &BF4Widget::onVarsHitIndicatorsEnabledCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsHudCommand,                     this, &BF4Widget::onVarsHudCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsIdleBanRoundsCommand,           this, &BF4Widget::onVarsIdleBanRoundsCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsIdleTimeoutCommand,             this, &BF4Widget::onVarsIdleTimeoutCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsKillCamCommand,                 this, &BF4Widget::onVarsKillCamCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsMaxPlayersCommand,              this, &BF4Widget::onVarsMaxPlayersCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsMaxSpectatorsCommand,           this, &BF4Widget::onVarsMaxSpectatorsCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsMiniMapCommand,                 this, &BF4Widget::onVarsMiniMapCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsMiniMapSpottingCommand,         this, &BF4Widget::onVarsMiniMapSpottingCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsNameTagCommand,                 this, &BF4Widget::onVarsNameTagCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsOnlySquadLeaderSpawnCommand,    this, &BF4Widget::onVarsOnlySquadLeaderSpawnCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsPlayerRespawnTimeCommand,       this, &BF4Widget::onVarsPlayerRespawnTimeCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsRegenerateHealthCommand,        this, &BF4Widget::onVarsRegenerateHealthCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsRoundLockdownCountdownCommand,  this, &BF4Widget::onVarsRoundLockdownCountdownCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsRoundRestartPlayerCountCommand, this, &BF4Widget::onVarsRoundRestartPlayerCountCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsRoundStartPlayerCountCommand,   this, &BF4Widget::onVarsRoundStartPlayerCountCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsRoundTimeLimitCommand,          this, &BF4Widget::onVarsRoundTimeLimitCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsRoundWarmupTimeoutCommand,      this, &BF4Widget::onVarsRoundWarmupTimeoutCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsServerNameCommand,              this, &BF4Widget::onVarsServerNameCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsServerDescriptionCommand,       this, &BF4Widget::onVarsServerDescriptionCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsServerMessageCommand,           this, &BF4Widget::onVarsServerMessageCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsServerTypeCommand,              this, &BF4Widget::onVarsServerTypeCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsSoldierHealthCommand,           this, &BF4Widget::onVarsSoldierHealthCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsTicketBleedRateCommand,         this, &BF4Widget::onVarsTicketBleedRateCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsVehicleSpawnAllowedCommand,     this, &BF4Widget::onVarsVehicleSpawnAllowedCommand);
    connect(commandHandler, &BF4CommandHandler::onVarsVehicleSpawnDelayCommand,       this, &BF4Widget::onVarsVehicleSpawnDelayCommand);

    /* User Interface */
    // Server Information
    connect(ui->pushButton_si_restartRound, &QPushButton::clicked, this, &BF4Widget::pushButton_si_restartRound_clicked);
    connect(ui->pushButton_si_runNextRound, &QPushButton::clicked, this, &BF4Widget::pushButton_si_runNextRound_clicked);

    // Events

    // Options -> Details
    connect(ui->lineEdit_op_so_serverName,        &QLineEdit::editingFinished, this, &BF4Widget::lineEdit_op_so_serverName_editingFinished);
    connect(ui->textEdit_op_so_serverDescription, &QTextEdit::textChanged,     this, &BF4Widget::textEdit_op_so_serverDescription_textChanged);
    connect(ui->lineEdit_op_so_serverMessage,     &QLineEdit::editingFinished, this, &BF4Widget::lineEdit_op_so_serverMessage_editingFinished);

    // Options -> Configuration
    connect(ui->checkBox_so_co_punkBuster,            &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_co_punkBuster_toggled);
    connect(ui->checkBox_so_co_fairFight,             &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_co_fairFight_toggled);
    connect(ui->checkBox_so_co_idleTimeout,           &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_co_idleTimeout_toggled);
    connect(ui->spinBox_so_co_idleTimeout,            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &BF4Widget::spinBox_so_co_idleTimeout_valueChanged);
    connect(ui->checkBox_so_co_idleBanRounds,         &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_co_idleBanRounds_toggled);
    connect(ui->spinBox_so_co_idleBanRounds,          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &BF4Widget::spinBox_so_co_idleBanRounds_valueChanged);
    connect(ui->checkBox_so_co_aggressiveJoin,        &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_co_aggressiveJoin_toggled);
    connect(ui->spinBox_so_co_maxPlayers,             static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &BF4Widget::spinBox_so_co_maxPlayers_valueChanged);
    connect(ui->spinBox_so_co_maxSpectators,          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &BF4Widget::spinBox_so_co_maxSpectators_valueChanged);
    connect(ui->checkBox_so_co_alwaysAllowSpectators, &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_co_alwaysAllowSpectators_toggled);
    connect(ui->checkBox_so_co_commander,             &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_co_commander_toggled);

    // Options -> Gameplay
    connect(ui->checkBox_so_gp_friendlyFire,              &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_gp_friendlyFire_toggled);
    connect(ui->checkBox_so_gp_autoBalance,               &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_gp_autoBalance_toggled);
    connect(ui->checkBox_so_gp_killCam,                   &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_gp_killCam_toggled);
    connect(ui->checkBox_so_gp_miniMap,                   &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_gp_miniMap_toggled);
    connect(ui->checkBox_so_gp_miniMapSpotting,           &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_gp_miniMapSpotting_toggled);
    connect(ui->checkBox_so_gp_3dSpotting,                &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_gp_3dSpotting_toggled);
    connect(ui->checkBox_so_gp_nameTag,                   &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_gp_nameTag_toggled);
    connect(ui->checkBox_so_gp_regenerateHealth,          &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_gp_regenerateHealth_toggled);
    connect(ui->checkBox_so_gp_hud,                       &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_gp_hud_toggled);
    connect(ui->checkBox_so_gp_onlySquadLeaderSpawn,      &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_gp_onlySquadLeaderSpawn_toggled);
    connect(ui->checkBox_so_gp_vehicleSpawnAllowed,       &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_gp_vehicleSpawnAllowed_toggled);
    connect(ui->checkBox_so_gp_hitIndicatorsEnabled,      &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_gp_hitIndicatorsEnabled_toggled);
    connect(ui->checkBox_so_gp_thirdPersonVehicleCameras, &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_gp_thirdPersonVehicleCameras_toggled);
    connect(ui->checkBox_so_gp_forceReloadWholeMags,      &QCheckBox::toggled,                                           this, &BF4Widget::checkBox_so_gp_forceReloadWholeMags_toggled);
    connect(ui->spinBox_so_gp_bulletDamage,               static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &BF4Widget::spinBox_so_gp_bulletDamage_valueChanged);
    connect(ui->spinBox_so_gp_soldierHealth,              static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &BF4Widget::spinBox_so_gp_soldierHealth_valueChanged);
    connect(ui->spinBox_so_gp_vehicleSpawnDelay,          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &BF4Widget::spinBox_so_gp_vehicleSpawnDelay_valueChanged);
    connect(ui->spinBox_so_gp_playerRespawnTime,          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &BF4Widget::spinBox_so_gp_playerRespawnTime_valueChanged);
    connect(ui->spinBox_so_gp_ticketBleedRate,            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &BF4Widget::spinBox_so_gp_ticketBleedRate_valueChanged);
    connect(ui->spinBox_so_gp_gameModeCounter,            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &BF4Widget::spinBox_so_gp_gameModeCounter_valueChanged);
    connect(ui->spinBox_so_gp_roundTimeLimit,             static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &BF4Widget::spinBox_so_gp_roundTimeLimit_valueChanged);
    connect(ui->spinBox_so_gp_roundLockdownCountdown,     static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &BF4Widget::spinBox_so_gp_roundLockdownCountdown_valueChanged);
    connect(ui->spinBox_so_gp_roundWarmupTimeout,         static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &BF4Widget::spinBox_so_gp_roundWarmupTimeout_valueChanged);
    connect(ui->spinBox_so_gp_roundRestartPlayerCount,    static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &BF4Widget::spinBox_so_gp_roundRestartPlayerCount_valueChanged);
    connect(ui->spinBox_so_gp_roundStartPlayerCount,      static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &BF4Widget::spinBox_so_gp_roundStartPlayerCount_valueChanged);

    // Banlist
    connect(ui->tableWidget_bl_banList, &QTreeWidget::customContextMenuRequested, this, &BF4Widget::tableWidget_bl_banList_customContextMenuRequested);
    connect(action_bl_banList_remove,   &QAction::triggered,                      this, &BF4Widget::action_bl_banList_remove_triggered);
}

BF4Widget::~BF4Widget()
{
    delete ui;

    delete playerListWidget;
    delete chatWidget;
    delete mapListWidget;
    delete reservedSlotsWidget;
    delete spectatorSlotsWidget;
    delete consoleWidget;
}

void BF4Widget::setAuthenticated(bool auth)
{
    authenticated = auth;

    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(playerListWidget), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(chatWidget), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_op), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(mapListWidget), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(ui->tab_bl), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(reservedSlotsWidget), auth);
    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(spectatorSlotsWidget), auth);

    startupCommands(auth);
}

void BF4Widget::startupCommands(bool auth)
{
    // Misc
    commandHandler->sendVersionCommand();
    commandHandler->sendServerInfoCommand();

    if (auth) {
        commandHandler->sendAdminEventsEnabledCommand(true);

        // Admins
        commandHandler->sendAdminPasswordCommand();

        // Banning
        commandHandler->sendBanListListCommand();

        // FairFight
        commandHandler->sendFairFightIsActiveCommand();

        // Player

        // Punkbuster
        commandHandler->sendPunkBusterIsActiveCommand();
        commandHandler->sendPunkBusterPbSvCommand("pb_sv_plist");

        // Squad

        // Variables
        commandHandler->sendVars3dSpottingCommand();
        commandHandler->sendVars3pCamCommand();
        commandHandler->sendVarsAlwaysAllowSpectatorsCommand();
        commandHandler->sendVarsAutoBalanceCommand();
        commandHandler->sendVarsBulletDamageCommand();
        commandHandler->sendVarsCommanderCommand();
        commandHandler->sendVarsForceReloadWholeMagsCommand();
        commandHandler->sendVarsFriendlyFireCommand();
        commandHandler->sendVarsGameModeCounterCommand();
        commandHandler->sendVarsGamePasswordCommand();
        commandHandler->sendVarsHitIndicatorsEnabledCommand();
        commandHandler->sendVarsHudCommand();
        commandHandler->sendVarsIdleBanRoundsCommand();
        commandHandler->sendVarsIdleTimeoutCommand();
        commandHandler->sendVarsKillCamCommand();
        commandHandler->sendVarsMaxPlayersCommand();
        commandHandler->sendVarsMaxSpectatorsCommand();
        commandHandler->sendVarsMiniMapCommand();
        commandHandler->sendVarsMiniMapSpottingCommand();
        commandHandler->sendVarsNameTagCommand();
        commandHandler->sendVarsOnlySquadLeaderSpawnCommand();
        commandHandler->sendVarsPlayerRespawnTimeCommand();
        commandHandler->sendVarsRegenerateHealthCommand();
        commandHandler->sendVarsRoundLockdownCountdownCommand();
        commandHandler->sendVarsRoundRestartPlayerCountCommand();
        commandHandler->sendVarsRoundStartPlayerCountCommand();
        commandHandler->sendVarsRoundTimeLimitCommand();
        commandHandler->sendVarsRoundWarmupTimeoutCommand();
        commandHandler->sendVarsServerNameCommand();
        commandHandler->sendVarsServerDescriptionCommand();
        commandHandler->sendVarsServerMessageCommand();
        commandHandler->sendVarsServerTypeCommand();
        commandHandler->sendVarsSoldierHealthCommand();
        commandHandler->sendVarsTicketBleedRateCommand();
        commandHandler->sendVarsVehicleSpawnAllowedCommand();
        commandHandler->sendVarsVehicleSpawnDelayCommand();
    }
}

void BF4Widget::logEvent(const QString &event, const QString &message)
{
    int row = ui->tableWidget_ev_events->rowCount();

    ui->tableWidget_ev_events->insertRow(row);
    ui->tableWidget_ev_events->setItem(row, 0, new QTableWidgetItem(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss")));
    ui->tableWidget_ev_events->setItem(row, 1, new QTableWidgetItem(event));
    ui->tableWidget_ev_events->setItem(row, 2, new QTableWidgetItem(message));
    ui->tableWidget_ev_events->resizeColumnsToContents();
}

/* Connection */
void BF4Widget::onConnected()
{
    setAuthenticated(false);

    logEvent("Connected", tr("Connected to %1:%2.").arg(con->socket->peerAddress().toString()).arg(con->socket->peerPort()));
}

void BF4Widget::onDisconnected()
{
    setAuthenticated(false);

    logEvent("Disconnected", tr("Disconnected."));
}

/* Events */
void BF4Widget::onPlayerAuthenticatedEvent(const QString &player)
{
    logEvent("PlayerAuthenticated", tr("Player %1 authenticated.").arg(player));
}

void BF4Widget::onPlayerDisconnectEvent(const QString &player)
{
    logEvent("PlayerDisconnect", tr("Player %1 disconnected.").arg(player));
}

void BF4Widget::onPlayerJoinEvent(const QString &player, const QString &guid)
{
    logEvent("PlayerJoin", tr("Player %1 joined the game (GUID: %2).").arg(player, guid));
}

void BF4Widget::onPlayerLeaveEvent(const QString &player, const QString &info)
{
    Q_UNUSED(info);

    logEvent("PlayerLeave", tr("Player %1 left the game.").arg(player)); // TODO: Impelment score stuffs here?
}

void BF4Widget::onPlayerSpawnEvent(const QString &player, int teamId)
{
    logEvent("PlayerSpawn", tr("Player %1 spawned, and is on team %2.").arg(player).arg(BF4LevelDictionary::getTeam(teamId - 1).name));
}

void BF4Widget::onPlayerKillEvent(const QString &killer, const QString &victim, const QString &weapon, bool headshot)
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

void BF4Widget::onPlayerChatEvent(const QString &sender, const QString &message, const QString &target)
{
    Q_UNUSED(target);

    logEvent("PlayerChat", QString("%1: %2").arg(sender).arg(message));
}

void BF4Widget::onPlayerSquadChangeEvent(const QString &player, int teamId, int squadId)
{
    Q_UNUSED(teamId);

    if (squadId != 0) {
        logEvent("PlayerSquadChange", tr("Player %1 changed squad to %2.").arg(player).arg(FrostbiteUtils::getSquadName(squadId)));
    }
}

void BF4Widget::onPlayerTeamChangeEvent(const QString &player, int teamId, int squadId)
{
    Q_UNUSED(squadId);

    logEvent("PlayerTeamChange", tr("Player %1 changed team to %2.").arg(player).arg(teamId));
}

void BF4Widget::onServerMaxPlayerCountChangeEvent()
{

}

void BF4Widget::onServerLevelLoadedEvent(const QString &levelName, const QString &gameModeName, int roundsPlayed, int roundsTotal)
{
    Q_UNUSED(roundsPlayed);
    Q_UNUSED(roundsTotal);

    LevelEntry level = BF4LevelDictionary::getLevel(levelName);
    GameModeEntry gameMode = BF4LevelDictionary::getGameMode(gameModeName);

    commandHandler->sendServerInfoCommand();

    logEvent("ServerLevelLoaded", tr("Loading level %1 with gamemode %2.").arg(level.name).arg(gameMode.name));
}

void BF4Widget::onServerRoundOverEvent(int winningTeamId)
{
    logEvent("ServerRoundOver", tr("The round has just ended, and %1 won.").arg(winningTeamId));
}

void BF4Widget::onServerRoundOverPlayersEvent(const QString &playerInfo)
{
    logEvent("ServerRoundOverPlayers", tr("The round has just ended, and %1 is the final detailed player stats.").arg(playerInfo)); // TODO: Check what this actually outputs.
}

void BF4Widget::onServerRoundOverTeamScoresEvent(const QString &teamScores)
{
    logEvent("ServerRoundOverTeamScores", tr("The round has just ended, and %1 is the final ticket/kill/life count for each team.").arg(teamScores));
}

/* Commands */
// Misc
void BF4Widget::onLoginHashedCommand(bool auth)
{
    if (auth) {
        // Call commands on startup.
        setAuthenticated(true);
    } else {
        int ret = QMessageBox::warning(0, tr("Error"), "Wrong password, make sure you typed in the right password and try again.");

        if (ret) {
            con->hostDisconnect();
        }
    }
}

void BF4Widget::onVersionCommand(const QString &type, int build)
{
    Q_UNUSED(type);

    ui->label_si_version->setText(tr("<b>Version</b>: %1").arg(getVersionFromBuild(build)));
    ui->label_si_version->setToolTip(QString::number(build));
}

void BF4Widget::onServerInfoCommand(const BF4ServerInfo &serverInfo)
{
    currentLevel = BF4LevelDictionary::getLevel(serverInfo.currentMap);
    currentGameMode = BF4LevelDictionary::getGameMode(serverInfo.gameMode);
    roundTime = serverInfo.roundTime;
    serverUpTime = serverInfo.serverUpTime;

    ui->label_si_level->setText(QString("<b>%1</b> - <b>%2</b>").arg(currentLevel.name).arg(currentGameMode.name));

    ui->label_si_level->setToolTip(tr("<table>"
                                          "<tr>"
                                              "<td>External IP address and port:</td>"
                                              "<td>%1</td>"
                                          "</tr>"
                                          "<tr>"
                                              "<td>Join queue enabled:</td>"
                                              "<td>%2</td>"
                                          "</tr>"
                                          "<tr>"
                                              "<td>Matchmaking enabled:</td>"
                                              "<td>%3</td>"
                                          "</tr>"

                                          "<tr>"
                                              "<td></td>"
                                          "</tr>"

                                          "<tr>"
                                              "<td>Region:</td>"
                                              "<td>%4</td>"
                                          "</tr>"
                                          "<tr>"
                                              "<td>Country:</td>"
                                              "<td>%5</td>"
                                          "</tr>"
                                          "<tr>"
                                              "<td>Closest ping site:</td>"
                                              "<td>%6</td>"
                                          "</tr>"

                                          "<tr>"
                                              "<td></td>"
                                          "</tr>"

                                          "<tr>"
                                              "<td>Blaze player count:</td>"
                                              "<td>%7</td>"
                                          "</tr>"
                                          "<tr>"
                                              "<td>Blaze game stat:</td>"
                                              "<td>%8</td>"
                                          "</tr>"
                                          "<tr>"
                                              "<td>Punkbuster Server:</td>"
                                              "<td>%9</td>"
                                          "</tr>"
                                      "</table>").arg(serverInfo.gameIpAndPort)
                                                 .arg(FrostbiteUtils::toString(serverInfo.joinQueueEnabled),
                                                      FrostbiteUtils::toString(serverInfo.matchMakingEnabled),
                                                      serverInfo.region,
                                                      serverInfo.country,
                                                      serverInfo.closestPingSite)
                                                 .arg(serverInfo.blazePlayerCount)
                                                 .arg(serverInfo.blazeGameState,
                                                      serverInfo.punkBusterVersion));

    ui->label_si_players->setText(tr("<b>Players</b>: %1 of %2").arg(serverInfo.playerCount).arg(serverInfo.maxPlayerCount));
    ui->label_si_round->setText(tr("<b>Round</b>: %1 of %2").arg(serverInfo.roundsPlayed + 1).arg(serverInfo.roundsTotal));
}

// Admin
void BF4Widget::onAdminPasswordCommand(const QString &password)
{
    ui->lineEdit_so_co_adminPassword->setText(password);
}

// Banning
void BF4Widget::onBanListListCommand(const BanList &banList)
{
    setBanlist(banList);
}

// FairFight
void BF4Widget::onFairFightIsActiveCommand(bool isActive)
{
    ui->checkBox_so_co_fairFight->setChecked(isActive);
}

// Player

// Punkbuster
void BF4Widget::onPunkBusterIsActiveCommand(bool active)
{
    ui->checkBox_so_co_punkBuster->setEnabled(!active);
    ui->checkBox_so_co_punkBuster->setChecked(active);
}

// Reserved Slots
void BF4Widget::onReservedSlotsListAggressiveJoinCommand(bool enabled)
{
    ui->checkBox_so_co_aggressiveJoin->setChecked(enabled);
}

// Squad

// Variables
void BF4Widget::onVars3dSpottingCommand(bool enabled)
{
    ui->checkBox_so_gp_3dSpotting->setChecked(enabled);
}

void BF4Widget::onVars3pCamCommand(bool enabled)
{
    ui->checkBox_so_gp_thirdPersonVehicleCameras->setChecked(enabled);
}

void BF4Widget::onVarsAlwaysAllowSpectatorsCommand(bool enabled)
{
    ui->checkBox_so_co_alwaysAllowSpectators->setEnabled(false);
    ui->checkBox_so_co_alwaysAllowSpectators->setChecked(enabled);

    ui->tabWidget->setTabEnabled(ui->tabWidget->indexOf(spectatorSlotsWidget), !enabled);
}

void BF4Widget::onVarsAutoBalanceCommand(bool enabled)
{
    ui->checkBox_so_gp_autoBalance->setChecked(enabled);
}

void BF4Widget::onVarsBulletDamageCommand(int percent)
{
    ui->spinBox_so_gp_bulletDamage->setEnabled(false);
    ui->spinBox_so_gp_bulletDamage->setValue(percent);
}

void BF4Widget::onVarsCommanderCommand(bool enabled)
{
    ui->checkBox_so_co_commander->setChecked(enabled);
}

void BF4Widget::onVarsForceReloadWholeMagsCommand(bool enabled)
{
    ui->checkBox_so_gp_forceReloadWholeMags->setChecked(enabled);
}

void BF4Widget::onVarsFriendlyFireCommand(bool enabled)
{
    ui->checkBox_so_gp_friendlyFire->setChecked(enabled);
}

void BF4Widget::onVarsGameModeCounterCommand(int percent)
{
    ui->spinBox_so_gp_gameModeCounter->setValue(percent);
}

void BF4Widget::onVarsGamePasswordCommand(const QString &password)
{
    ui->lineEdit_so_co_gamePassword->setText(password);
}

void BF4Widget::onVarsHitIndicatorsEnabledCommand(bool enabled)
{
    ui->checkBox_so_gp_hitIndicatorsEnabled->setChecked(enabled);
}

void BF4Widget::onVarsHudCommand(bool enabled)
{
    ui->checkBox_so_gp_hud->setChecked(enabled);
}

void BF4Widget::onVarsIdleBanRoundsCommand(int rounds)
{
    if (rounds <= 0) {
        ui->checkBox_so_co_idleBanRounds->setChecked(true);
        ui->spinBox_so_co_idleBanRounds->setEnabled(false);
    } else {
        ui->checkBox_so_co_idleBanRounds->setChecked(false);
    }

    ui->spinBox_so_co_idleBanRounds->setValue(rounds);
}

void BF4Widget::onVarsIdleTimeoutCommand(int timeout)
{
    if (timeout >= 84600) {
        ui->checkBox_so_co_idleTimeout->setChecked(true);
        ui->spinBox_so_co_idleTimeout->setEnabled(false);
    } else {
        ui->checkBox_so_co_idleTimeout->setChecked(false);
    }

    ui->spinBox_so_co_idleTimeout->setValue(timeout);
}

void BF4Widget::onVarsKillCamCommand(bool enabled)
{
    ui->checkBox_so_gp_killCam->setChecked(enabled);
}

void BF4Widget::onVarsMaxPlayersCommand(int playerCount)
{
    ui->spinBox_so_co_maxPlayers->setValue(playerCount);
}

void BF4Widget::onVarsMaxSpectatorsCommand(int spectatorCount)
{
    ui->spinBox_so_co_maxSpectators->setValue(spectatorCount);
}

void BF4Widget::onVarsMiniMapCommand(bool enabled)
{
    ui->checkBox_so_gp_miniMap->setChecked(enabled);
}

void BF4Widget::onVarsMiniMapSpottingCommand(bool enabled)
{
    ui->checkBox_so_gp_miniMapSpotting->setEnabled(false);
    ui->checkBox_so_gp_miniMapSpotting->setChecked(enabled);
}

void BF4Widget::onVarsNameTagCommand(bool enabled)
{
    ui->checkBox_so_gp_nameTag->setChecked(enabled);
}

void BF4Widget::onVarsOnlySquadLeaderSpawnCommand(bool enabled)
{
    ui->checkBox_so_gp_onlySquadLeaderSpawn->setChecked(enabled);
}

void BF4Widget::onVarsPlayerRespawnTimeCommand(int respawnTime)
{
    ui->spinBox_so_gp_playerRespawnTime->setValue(respawnTime);
}

void BF4Widget::onVarsRegenerateHealthCommand(bool enabled)
{
    ui->checkBox_so_gp_regenerateHealth->setChecked(enabled);
}

void BF4Widget::onVarsRoundLockdownCountdownCommand(int seconds)
{
    ui->spinBox_so_gp_roundLockdownCountdown->setValue(seconds);
}

void BF4Widget::onVarsRoundRestartPlayerCountCommand(int players)
{
    ui->spinBox_so_gp_roundRestartPlayerCount->setValue(players);
}

void BF4Widget::onVarsRoundStartPlayerCountCommand(int players)
{
    ui->spinBox_so_gp_roundStartPlayerCount->setValue(players);
}

void BF4Widget::onVarsRoundTimeLimitCommand(int percentage)
{
    ui->spinBox_so_gp_roundTimeLimit->setValue(percentage);
}

void BF4Widget::onVarsRoundWarmupTimeoutCommand(int timeout)
{
    ui->spinBox_so_gp_roundWarmupTimeout->setValue(timeout);
}

void BF4Widget::onVarsServerNameCommand(const QString &serverName)
{
    ui->lineEdit_op_so_serverName->setText(serverName);
}

void BF4Widget::onVarsServerDescriptionCommand(const QString &serverDescription)
{
    ui->textEdit_op_so_serverDescription->setText(serverDescription);
}

void BF4Widget::onVarsServerMessageCommand(const QString &serverMessage)
{
    ui->lineEdit_op_so_serverMessage->setText(serverMessage);
}

void BF4Widget::onVarsServerTypeCommand(const QString &type)
{
    ui->label_so_co_serverType->setText(type);

    if (type == "RANKED") {
        ui->lineEdit_so_co_gamePassword->setEnabled(false);
    }
}

void BF4Widget::onVarsSoldierHealthCommand(int health)
{
    ui->spinBox_so_gp_soldierHealth->setValue(health);
}

void BF4Widget::onVarsTicketBleedRateCommand(int percent)
{
    ui->spinBox_so_gp_ticketBleedRate->setValue(percent);
}

void BF4Widget::onVarsVehicleSpawnAllowedCommand(bool enabled)
{
    ui->checkBox_so_gp_vehicleSpawnAllowed->setChecked(enabled);
}

void BF4Widget::onVarsVehicleSpawnDelayCommand(int delay)
{   
    ui->spinBox_so_gp_vehicleSpawnDelay->setValue(delay);
}

/* User Interface */
// ServerInfo
void BF4Widget::pushButton_si_restartRound_clicked()
{
    int ret = QMessageBox::question(this, tr("Restart round"), tr("Are you sure you want to restart the round?"));

    if (ret == QMessageBox::Yes) {
        commandHandler->sendMapListRestartRoundCommand();
    }
}

void BF4Widget::pushButton_si_runNextRound_clicked()
{
    int ret = QMessageBox::question(this, tr("Run next round"), tr("Are you sure you want to run the next round?"));

    if (ret == QMessageBox::Yes) {
        commandHandler->sendMapListRunNextRoundCommand();
    }
}

void BF4Widget::updateRoundTime()
{ 
    ui->label_si_round->setToolTip(FrostbiteUtils::toString(FrostbiteUtils::getTimeFromSeconds(roundTime++)));
}

void BF4Widget::updateUpTime()
{
    ui->label_si_upTime->setText(tr("<b>Uptime:</b> %1").arg(FrostbiteUtils::toString(FrostbiteUtils::getTimeFromSeconds(serverUpTime++))));
}

// Event

// BanList
void BF4Widget::tableWidget_bl_banList_customContextMenuRequested(const QPoint &pos)
{
    if (ui->tableWidget_bl_banList->itemAt(pos)) {
        menu_bl_banList->exec(QCursor::pos());
    }
}

void BF4Widget::action_bl_banList_remove_triggered()
{
    int row = ui->tableWidget_bl_banList->currentRow();
    QString idType = ui->tableWidget_bl_banList->item(row, 0)->text();
    QString player = ui->tableWidget_bl_banList->item(row, 1)->text();

    if (!idType.isEmpty() && !player.isEmpty()) {
        ui->tableWidget_bl_banList->removeRow(row);

        commandHandler->sendBanListRemoveCommand(idType, player);
    }
}

void BF4Widget::addBanListRow(const QString &idType, const QString &id, const QString &banType, int seconds, int rounds, const QString &reason)
{
    int row = ui->tableWidget_bl_banList->rowCount();

    ui->tableWidget_bl_banList->insertRow(row);
    ui->tableWidget_bl_banList->setItem(row, 0, new QTableWidgetItem(idType));
    ui->tableWidget_bl_banList->setItem(row, 1, new QTableWidgetItem(id));
    ui->tableWidget_bl_banList->setItem(row, 2, new QTableWidgetItem(banType));
    ui->tableWidget_bl_banList->setItem(row, 3, new QTableWidgetItem(QString::number(seconds)));
    ui->tableWidget_bl_banList->setItem(row, 4, new QTableWidgetItem(QString::number(rounds)));
    ui->tableWidget_bl_banList->setItem(row, 5, new QTableWidgetItem(reason));
}

void BF4Widget::setBanlist(const BanList &banList)
{
    ui->tableWidget_bl_banList->clearContents();
    ui->tableWidget_bl_banList->setRowCount(0);

    for (BanListEntry entry : banList) {
        addBanListRow(entry.idType, entry.id, entry.banType, entry.seconds, entry.rounds, entry.reason);
    }
}

// Options -> Details
void BF4Widget::lineEdit_op_so_serverName_editingFinished()
{
    QString serverName = ui->lineEdit_op_so_serverName->text();

    if (!serverName.isEmpty()) {
        commandHandler->sendVarsServerNameCommand(serverName);
    }
}

void BF4Widget::textEdit_op_so_serverDescription_textChanged()
{
    QString serverDescription = ui->textEdit_op_so_serverDescription->toPlainText();

    if (!serverDescription.isEmpty()) {
        commandHandler->sendVarsServerDescriptionCommand(serverDescription);
    }
}

void BF4Widget::lineEdit_op_so_serverMessage_editingFinished()
{
    QString serverMessage = ui->lineEdit_op_so_serverMessage->text();

    if (!serverMessage.isEmpty()) {
        commandHandler->sendVarsServerMessageCommand(serverMessage);
    }
}

// Options -> Configuration
void BF4Widget::checkBox_so_co_punkBuster_toggled(bool checked)
{
    if (checked) {
        commandHandler->sendPunkBusterActivateCommand();
    }
}

void BF4Widget::checkBox_so_co_fairFight_toggled(bool checked)
{
    if (checked) {
        commandHandler->sendFairFightActivateCommand();
    } else {
        commandHandler->sendFairFightDeactivateCommand();
    }

    commandHandler->sendFairFightIsActiveCommand();
}

void BF4Widget::checkBox_so_co_idleTimeout_toggled(bool checked)
{
    int timeout = checked ? 84600 : 225;

    ui->spinBox_so_co_idleTimeout->setEnabled(!checked);
    ui->spinBox_so_co_idleTimeout->setValue(timeout);
    ui->checkBox_so_co_idleBanRounds->setEnabled(!checked);
    ui->checkBox_so_co_idleBanRounds->setChecked(checked);
    checkBox_so_co_idleBanRounds_toggled(checked);

    commandHandler->sendVarsIdleTimeoutCommand(timeout);
}

void BF4Widget::spinBox_so_co_idleTimeout_valueChanged(int value)
{
    if (value >= 225) {
        commandHandler->sendVarsIdleTimeoutCommand(value);
    }
}

void BF4Widget::checkBox_so_co_idleBanRounds_toggled(bool checked)
{
    int rounds = checked ? 0 : 2;

    ui->spinBox_so_co_idleBanRounds->setEnabled(!checked);
    ui->spinBox_so_co_idleBanRounds->setValue(rounds);

    commandHandler->sendVarsIdleBanRoundsCommand(rounds);
}

void BF4Widget::spinBox_so_co_idleBanRounds_valueChanged(int value)
{
    if (value > 0) {
        commandHandler->sendVarsIdleTimeoutCommand(value);
    }
}

void BF4Widget::checkBox_so_co_aggressiveJoin_toggled(bool checked)
{
    commandHandler->sendReservedSlotsListAggressiveJoinCommand(checked);
}

void BF4Widget::spinBox_so_co_maxPlayers_valueChanged(int value)
{
    commandHandler->sendVarsMaxPlayersCommand(value);
}

void BF4Widget::spinBox_so_co_maxSpectators_valueChanged(int value)
{
    commandHandler->sendVarsMaxSpectatorsCommand(value);
}

void BF4Widget::checkBox_so_co_alwaysAllowSpectators_toggled(bool checked)
{
    commandHandler->sendVarsAlwaysAllowSpectatorsCommand(checked);
}

void BF4Widget::checkBox_so_co_commander_toggled(bool checked)
{
    commandHandler->sendVarsCommanderCommand(checked);
}

// Options -> Gameplay
void BF4Widget::checkBox_so_gp_friendlyFire_toggled(bool checked)
{
    commandHandler->sendVarsFriendlyFireCommand(checked);
}

void BF4Widget::checkBox_so_gp_autoBalance_toggled(bool checked)
{
    commandHandler->sendVarsAutoBalanceCommand(checked);
}

void BF4Widget::checkBox_so_gp_killCam_toggled(bool checked)
{
    commandHandler->sendVarsKillCamCommand(checked);
}

void BF4Widget::checkBox_so_gp_miniMap_toggled(bool checked)
{
    commandHandler->sendVarsMiniMapCommand(checked);
}

void BF4Widget::checkBox_so_gp_miniMapSpotting_toggled(bool checked)
{
    commandHandler->sendVarsMiniMapSpottingCommand(checked);
}

void BF4Widget::checkBox_so_gp_3dSpotting_toggled(bool checked)
{
    commandHandler->sendVars3dSpottingCommand(checked);
}

void BF4Widget::checkBox_so_gp_nameTag_toggled(bool checked)
{
    commandHandler->sendVarsNameTagCommand(checked);
}

void BF4Widget::checkBox_so_gp_regenerateHealth_toggled(bool checked)
{
    commandHandler->sendVarsRegenerateHealthCommand(checked);
}

void BF4Widget::checkBox_so_gp_hud_toggled(bool checked)
{
    commandHandler->sendVarsHudCommand(checked);
}

void BF4Widget::checkBox_so_gp_onlySquadLeaderSpawn_toggled(bool checked)
{
    commandHandler->sendVarsOnlySquadLeaderSpawnCommand(checked);
}

void BF4Widget::checkBox_so_gp_vehicleSpawnAllowed_toggled(bool checked)
{
    commandHandler->sendVarsVehicleSpawnAllowedCommand(checked);
}

void BF4Widget::checkBox_so_gp_hitIndicatorsEnabled_toggled(bool checked)
{
    commandHandler->sendVarsHitIndicatorsEnabledCommand(checked);
}

void BF4Widget::checkBox_so_gp_thirdPersonVehicleCameras_toggled(bool checked)
{
    commandHandler->sendVars3pCamCommand(checked);
}

void BF4Widget::checkBox_so_gp_forceReloadWholeMags_toggled(bool checked)
{
    commandHandler->sendVarsForceReloadWholeMagsCommand(checked);
}

void BF4Widget::spinBox_so_gp_bulletDamage_valueChanged(int value)
{
    commandHandler->sendVarsBulletDamageCommand(value);
}

void BF4Widget::spinBox_so_gp_soldierHealth_valueChanged(int value)
{
    commandHandler->sendVarsSoldierHealthCommand(value);
}

void BF4Widget::spinBox_so_gp_vehicleSpawnDelay_valueChanged(int value)
{
    commandHandler->sendVarsVehicleSpawnDelayCommand(value);
}

void BF4Widget::spinBox_so_gp_playerRespawnTime_valueChanged(int value)
{
    commandHandler->sendVarsPlayerRespawnTimeCommand(value);
}

void BF4Widget::spinBox_so_gp_ticketBleedRate_valueChanged(int value)
{
    commandHandler->sendVarsTicketBleedRateCommand(value);
}

void BF4Widget::spinBox_so_gp_gameModeCounter_valueChanged(int value)
{
    commandHandler->sendVarsGameModeCounterCommand(value);
}

void BF4Widget::spinBox_so_gp_roundTimeLimit_valueChanged(int value)
{
    commandHandler->sendVarsRoundTimeLimitCommand(value);
}

void BF4Widget::spinBox_so_gp_roundLockdownCountdown_valueChanged(int value)
{
    commandHandler->sendVarsRoundLockdownCountdownCommand(value);
}

void BF4Widget::spinBox_so_gp_roundWarmupTimeout_valueChanged(int value)
{
    commandHandler->sendVarsRoundWarmupTimeoutCommand(value);
}

void BF4Widget::spinBox_so_gp_roundRestartPlayerCount_valueChanged(int value)
{
    commandHandler->sendVarsRoundRestartPlayerCountCommand(value);
}

void BF4Widget::spinBox_so_gp_roundStartPlayerCount_valueChanged(int value)
{
    commandHandler->sendVarsRoundStartPlayerCountCommand(value);
}
