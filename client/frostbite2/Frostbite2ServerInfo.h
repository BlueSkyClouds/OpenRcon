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

#ifndef FROSTBITE2SERVERINFO_H
#define FROSTBITE2SERVERINFO_H

#include <QString>

#include "ServerInfo.h"

class Frostbite2ServerInfo : public ServerInfo
{
public:
    Frostbite2ServerInfo(const QString &serverName,
               int playerCount,
               int maxPlayerCount,
               const QString &gameMode,
               const QString &currentMap,
               int roundsPlayed,
               int roundsTotal,
               const TeamScores &scores,
               const OnlineState &onlineState,
               bool ranked,
               bool punkBuster,
               bool hasGamePassword,
               int&serverUpTime,
               int roundTime,
               const QString &gameIpAndPort,
               const QString &punkBusterVersion,
               bool joinQueueEnabled,
               const QString &region,
               const QString &closestPingSite,
               const QString &country,
               bool matchMakingEnabled);
    ~Frostbite2ServerInfo();

    QString getGameIpAndPort();
    QString getPunkBusterVersion();
    bool getJoinQueueEnabled();
    QString getRegion();
    QString getClosestPingSite();
    QString getCountry();
    bool getMatchMakingEnabled();

private:
    QString gameIpAndPort;
    QString punkBusterVersion;
    bool joinQueueEnabled;
    QString region;
    QString closestPingSite;
    QString country;
    bool matchMakingEnabled;

};

#endif // FROSTBITE2SERVERINFO_H
