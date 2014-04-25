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

#include "BFBaseCommandHandler.h"

BFBaseCommandHandler::BFBaseCommandHandler(QObject *parent) : FrostbiteCommandHandler(parent)
{

}

BFBaseCommandHandler::~BFBaseCommandHandler()
{

}

void BFBaseCommandHandler::parse(const QString &command, const FrostbiteRconPacket &packet, const FrostbiteRconPacket &lastSentPacket)
{
    Q_UNUSED(command);
    Q_UNUSED(packet);
    Q_UNUSED(lastSentPacket);

    // TODO: Commands that are common in Battlefield games should be terminated here.
}
