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

#include "BF4LevelDictionary.h"
#include "TeamEntry.h"
#include "LevelEntry.h"
#include "BF4GameModeEntry.h"
#include "GameModeLevel.h"

template<>
QList<TeamEntry> BF4LevelDictionary::teamList = {
    /* List of all teams */
<<<<<<< HEAD
    TeamEntry("Neutral", ""),                  // 0
    TeamEntry("US",     ":/bf4/teams/US.png"), // 1
    TeamEntry("RU",     ":/bf4/teams/RU.png"), // 2
    TeamEntry("CN",     ":/bf4/teams/CN.png"), // 3
=======
    TeamEntry("Neutral"),                  // 0
    TeamEntry("RU", ":/bf4/teams/RU.png"), // 1
    TeamEntry("US", ":/bf4/teams/US.png"), // 2
    TeamEntry("CN", ":/bf4/teams/CN.png"), // 3
>>>>>>> master
};

template<>
QString BF4LevelDictionary::imagePath = ":/bf4/levels";

template<>
QList<LevelEntry> BF4LevelDictionary::levelList = {
    /* List of all levels */
    LevelEntry("MP_Abandoned",  "Zavod 311",            imagePath, "zavod_311.png"),           // 0
    LevelEntry("MP_Damage",     "Lancang Dam",          imagePath, "lancang_dam.png"),         // 1
    LevelEntry("MP_Flooded",    "Flood Zone",           imagePath, "flood_zone.png"),          // 2
    LevelEntry("MP_Journey",    "Golmud Railway",       imagePath, "golmud_railway.png"),      // 3
    LevelEntry("MP_Naval",      "Paracel Storm",        imagePath, "paracel_storm.png"),       // 4
    LevelEntry("MP_Prison",     "Operation Locker",     imagePath, "operation_locker.png"),    // 5
    LevelEntry("MP_Resort",     "Hainan Resort",        imagePath, "hainan_resort.png"),       // 6
    LevelEntry("MP_Siege",      "Siege of Shanghai",    imagePath, "seige_of_shanghai.png"),   // 7
    LevelEntry("MP_TheDish",    "Rogue Transmission",   imagePath, "rogue_transmission.png"),  // 8
    LevelEntry("MP_Tremors",    "Dawnbreaker",          imagePath, "dawnbreaker.png"),         // 9

    // XP1 (China Rising)
    LevelEntry("XP1_001",       "Silk Road",            imagePath, "silk_road.png"),           // 10
    LevelEntry("XP1_002",       "Altai Range",          imagePath, "altai_range.png"),         // 11
    LevelEntry("XP1_003",       "Guilin Peaks",         imagePath, "guilin_peaks.png"),        // 12
    LevelEntry("XP1_004",       "Dragon Pass",          imagePath, "dragon_pass.png"),         // 13

    // XP2 (Second Assault)
    LevelEntry("XP0_Caspian",   "Caspian Border 2014",  imagePath, "caspian_border_2014.png"), // 14
    LevelEntry("XP0_Firestorm", "Firestorm 2014",       imagePath, "firestorm_2014.png"),      // 15
    LevelEntry("XP0_Metro",     "Operation Metro 2014", imagePath, "operation_metro_2014.png"), // 16
    LevelEntry("XP0_Oman",      "Gulf of Oman 2014",    imagePath, "gulf_of_oman_2014.png"),   // 17

    // XP3 (Naval Strike)
    LevelEntry("XP2_001",       "Lost Islands",         imagePath, "lost_islands.png"),        // 18
    LevelEntry("XP2_002",       "Nansha Strike",        imagePath, "nansha_strike.png"),       // 19
    LevelEntry("XP2_003",       "Wave Breaker",         imagePath, "wave_breaker.png"),        // 20
    LevelEntry("XP2_004",       "Operation Mortar",     imagePath, "operation_mortar.png"),    // 21

    // XP4 (Dragon's Teeth)
    LevelEntry("XP3_MarketPl",  "Pearl Market",         imagePath, "pearl_market.png"),        // 22
    LevelEntry("XP3_Prpganda",  "Propaganda",           imagePath, "propaganda.png"),          // 23
    LevelEntry("XP3_UrbanGdn",  "Lumphini Garden",      imagePath, "lumphini_garden.png"),     // 24
    LevelEntry("XP3_WtrFront",  "Sunken Dragon",        imagePath, "sunken_dragon.png"),       // 25

    // XP5 (Final Stand)
<<<<<<< HEAD
    LevelEntry("XP4_Arctic",    "Operation Whiteout",   imagePath, "operation_whiteout.png"),  // 26
    LevelEntry("XP4_SubBase",   "Hammerhead",           imagePath, "hammerhead.png"),          // 27
    LevelEntry("XP4_Titan",     "Giants Of Karelia",    imagePath, "giants_of_karelia.png"),   // 28
    LevelEntry("XP4_Wlkrftry",  "Hangar 21",            imagePath, "hangar_21.png"),           // 29
=======
    LevelEntry("XP4_Arctic",    "Operation Whiteout",   QList<int>({ 2, 1 }), imagePath, "operation_whiteout.png"),   // 26
    LevelEntry("XP4_SubBase",   "Hammerhead",           QList<int>({ 2, 1 }), imagePath, "hammerhead.png"),           // 27
    LevelEntry("XP4_Titan",     "Hangar 21",            QList<int>({ 2, 1 }), imagePath, "hangar_21.png"),            // 28
    LevelEntry("XP4_Wlkrftry",  "Giants Of Karelia",    QList<int>({ 2, 1 }), imagePath, "giants_of_karelia.png"),    // 29
>>>>>>> master

};

template<>
QList<BF4GameModeEntry> BF4LevelDictionary::gameModeList = {
    /* List of all gamemodes */
    BF4GameModeEntry("ConquestLarge0",       "Conquest Large",        64, 2, 4), // 0
    BF4GameModeEntry("ConquestSmall0",       "Conquest Small",        32, 2, 4), // 1
    BF4GameModeEntry("Domination0",          "Domination",            20, 0, 4), // 2
    BF4GameModeEntry("Elimination0",         "Defuse",                10, 0, 4), // 3
    BF4GameModeEntry("Obliteration",         "Obliteration",          32, 2, 4), // 4
    BF4GameModeEntry("RushLarge0",           "Rush",                  32, 2, 4), // 5
    BF4GameModeEntry("SquadDeathMatch0",     "Squad Deathmatch",      20, 0, 4), // 6
    BF4GameModeEntry("TeamDeathMatch0",      "Team Deathmatch",       20, 0, 4), // 7
    BF4GameModeEntry("AirSuperiority0",      "Air Superiority",       24, 0, 4), // 8
    BF4GameModeEntry("CaptureTheFlag0",      "Capture the flag",      32, 0, 4), // 9
    BF4GameModeEntry("CarrierAssaultSmall0", "Carrier Assault Small", 32, 2, 4), // 10
    BF4GameModeEntry("CarrierAssaultLarge0", "Carrier Assault Large", 64, 2, 4), // 11
    BF4GameModeEntry("Chainlink0",           "Chain Link",            32, 0, 4)  // 12
};

template<>
QList<GameModeLevel> BF4LevelDictionary::levelMap = {
    /* List of all levels and gamemodes combined */
    /* ConquestLarge0 */
    GameModeLevel(0, 0,   QList<int>({ 2, 1 })),
    GameModeLevel(0, 1,   QList<int>({ 2, 3 })),
    GameModeLevel(0, 2,   QList<int>({ 1, 3 })),
    GameModeLevel(0, 3,   QList<int>({ 2, 3 })),
    GameModeLevel(0, 4,   QList<int>({ 1, 3 })),
    GameModeLevel(0, 5,   QList<int>({ 1, 2 })),
    GameModeLevel(0, 6,   QList<int>({ 1, 3 })),
    GameModeLevel(0, 7,   QList<int>({ 1, 3 })),
    GameModeLevel(0, 8,   QList<int>({ 2, 3 })),
    GameModeLevel(0, 9,   QList<int>({ 1, 3 })),

    // XP1 (China Rising)
    GameModeLevel(0, 10,  QList<int>({ 1, 3 })),
    GameModeLevel(0, 11,  QList<int>({ 1, 3 })),
    GameModeLevel(0, 12,  QList<int>({ 1, 3 })),
    GameModeLevel(0, 13,  QList<int>({ 1, 3 })),

    // XP2 (Second Assault)
    GameModeLevel(0, 14,  QList<int>({ 1, 2 })),
    GameModeLevel(0, 15,  QList<int>({ 1, 2 })),
    GameModeLevel(0, 16,  QList<int>({ 1, 2 })),
    GameModeLevel(0, 17,  QList<int>({ 1, 2 })),

    // XP3 (Naval Strike)
    GameModeLevel(0, 18,  QList<int>({ 1, 2 })),
    GameModeLevel(0, 19,  QList<int>({ 1, 2 })),
    GameModeLevel(0, 20,  QList<int>({ 1, 2 })),
    GameModeLevel(0, 21,  QList<int>({ 1, 2 })),

    // XP4 (Dragon's Teeth)
    GameModeLevel(0, 22,  QList<int>({ 1, 3 })),
    GameModeLevel(0, 23,  QList<int>({ 1, 3 })),
    GameModeLevel(0, 24,  QList<int>({ 1, 3 })),
    GameModeLevel(0, 25,  QList<int>({ 1, 3 })),

    // XP5 (Final Stand)
    GameModeLevel(0, 26,  QList<int>({ 1, 2 })),
    GameModeLevel(0, 27,  QList<int>({ 1, 2 })),
    GameModeLevel(0, 28,  QList<int>({ 1, 2 })),
    GameModeLevel(0, 29,  QList<int>({ 1, 2 })),

    /* ConquestSmall0 */
    GameModeLevel(1, 0,   QList<int>({ 2, 1 })),
    GameModeLevel(1, 1,   QList<int>({ 2, 3 })),
    GameModeLevel(1, 2,   QList<int>({ 1, 3 })),
    GameModeLevel(1, 3,   QList<int>({ 2, 3 })),
    GameModeLevel(1, 4,   QList<int>({ 1, 3 })),
    GameModeLevel(1, 5,   QList<int>({ 1, 2 })),
    GameModeLevel(1, 6,   QList<int>({ 1, 3 })),
    GameModeLevel(1, 7,   QList<int>({ 1, 3 })),
    GameModeLevel(1, 8,   QList<int>({ 2, 3 })),
    GameModeLevel(1, 9,   QList<int>({ 1, 3 })),

    // XP1 (China Rising)
    GameModeLevel(1, 10,  QList<int>({ 1, 3 })),
    GameModeLevel(1, 11,  QList<int>({ 1, 3 })),
    GameModeLevel(1, 12,  QList<int>({ 1, 3 })),
    GameModeLevel(1, 13,  QList<int>({ 1, 3 })),

    // XP2 (Second Assault)
    GameModeLevel(1, 14,  QList<int>({ 1, 2 })),
    GameModeLevel(1, 15,  QList<int>({ 1, 2 })),
    GameModeLevel(1, 16,  QList<int>({ 1, 2 })),
    GameModeLevel(1, 17,  QList<int>({ 1, 2 })),

    // XP3 (Naval Strike)
    GameModeLevel(1, 18,  QList<int>({ 1, 2 })),
    GameModeLevel(1, 19,  QList<int>({ 1, 2 })),
    GameModeLevel(1, 20,  QList<int>({ 1, 2 })),
    GameModeLevel(1, 21,  QList<int>({ 1, 2 })),

    // XP4 (Dragon's Teeth)
    GameModeLevel(1, 22,  QList<int>({ 1, 3 })),
    GameModeLevel(1, 23,  QList<int>({ 1, 3 })),
    GameModeLevel(1, 24,  QList<int>({ 1, 3 })),
    GameModeLevel(1, 25,  QList<int>({ 1, 3 })),

    // XP5 (Final Stand)
    GameModeLevel(1, 26,  QList<int>({ 1, 2 })),
    GameModeLevel(1, 27,  QList<int>({ 1, 2 })),
    GameModeLevel(1, 28,  QList<int>({ 1, 2 })),
    GameModeLevel(1, 29,  QList<int>({ 1, 2 })),

    /* Domination0 */
    GameModeLevel(2, 0,   QList<int>({ 2, 1 })),
    GameModeLevel(2, 1,   QList<int>({ 2, 3 })),
    GameModeLevel(2, 2,   QList<int>({ 1, 3 })),
    GameModeLevel(2, 3,   QList<int>({ 2, 3 })),
    GameModeLevel(2, 4,   QList<int>({ 1, 3 })),
    GameModeLevel(2, 5,   QList<int>({ 1, 2 })),
    GameModeLevel(2, 6,   QList<int>({ 1, 3 })),
    GameModeLevel(2, 7,   QList<int>({ 1, 3 })),
    GameModeLevel(2, 8,   QList<int>({ 2, 3 })),
    GameModeLevel(2, 9,   QList<int>({ 1, 3 })),

    // XP1 (China Rising)
    GameModeLevel(2, 10,  QList<int>({ 1, 3 })),
    GameModeLevel(2, 11,  QList<int>({ 1, 3 })),
    GameModeLevel(2, 12,  QList<int>({ 1, 3 })),
    GameModeLevel(2, 13,  QList<int>({ 1, 3 })),

    // XP2 (Second Assault)
    GameModeLevel(2, 14,  QList<int>({ 1, 2 })),
    GameModeLevel(2, 15,  QList<int>({ 1, 2 })),
    GameModeLevel(2, 16,  QList<int>({ 1, 2 })),
    GameModeLevel(2, 17,  QList<int>({ 1, 2 })),

    // XP3 (Naval Strike)
    GameModeLevel(2, 18,  QList<int>({ 1, 2 })),
    GameModeLevel(2, 19,  QList<int>({ 1, 2 })),
    GameModeLevel(2, 20,  QList<int>({ 1, 2 })),
    GameModeLevel(2, 21,  QList<int>({ 1, 2 })),

    // XP4 (Dragon's Teeth)
    GameModeLevel(2, 22,  QList<int>({ 1, 3 })),
    GameModeLevel(2, 23,  QList<int>({ 1, 3 })),
    GameModeLevel(2, 24,  QList<int>({ 1, 3 })),
    GameModeLevel(2, 25,  QList<int>({ 1, 3 })),

    // XP5 (Final Stand)
    GameModeLevel(2, 26,  QList<int>({ 1, 2 })),
    GameModeLevel(2, 27,  QList<int>({ 1, 2 })),
    GameModeLevel(2, 28,  QList<int>({ 1, 2 })),
    GameModeLevel(2, 29,  QList<int>({ 1, 2 })),

    /* Elemination0 */
    GameModeLevel(3, 0,   QList<int>({ 2, 1 })),
    GameModeLevel(3, 1,   QList<int>({ 2, 3 })),
    GameModeLevel(3, 2,   QList<int>({ 1, 3 })),
    GameModeLevel(3, 3,   QList<int>({ 2, 3 })),
    GameModeLevel(3, 4,   QList<int>({ 1, 3 })),
    GameModeLevel(3, 5,   QList<int>({ 1, 2 })),
    GameModeLevel(3, 6,   QList<int>({ 1, 3 })),
    GameModeLevel(3, 7,   QList<int>({ 1, 3 })),
    GameModeLevel(3, 8,   QList<int>({ 2, 3 })),
    GameModeLevel(3, 9,   QList<int>({ 1, 3 })),

    // XP1 (China Rising)
    GameModeLevel(3, 10,  QList<int>({ 1, 3 })),
    GameModeLevel(3, 11,  QList<int>({ 1, 3 })),
    GameModeLevel(3, 12,  QList<int>({ 1, 3 })),
    GameModeLevel(3, 13,  QList<int>({ 1, 3 })),

    // XP2 (Second Assault)
    GameModeLevel(3, 14,  QList<int>({ 1, 2 })),
    GameModeLevel(3, 15,  QList<int>({ 1, 2 })),
    GameModeLevel(3, 16,  QList<int>({ 1, 2 })),
    GameModeLevel(3, 17,  QList<int>({ 1, 2 })),

    // XP3 (Naval Strike)
    GameModeLevel(3, 18,  QList<int>({ 1, 2 })),
    GameModeLevel(3, 19,  QList<int>({ 1, 2 })),
    GameModeLevel(3, 20,  QList<int>({ 1, 2 })),
    GameModeLevel(3, 21,  QList<int>({ 1, 2 })),

    // XP4 (Dragon's Teeth)
    GameModeLevel(3, 22,  QList<int>({ 1, 3 })),
    GameModeLevel(3, 23,  QList<int>({ 1, 3 })),
    GameModeLevel(3, 24,  QList<int>({ 1, 3 })),
    GameModeLevel(3, 25,  QList<int>({ 1, 3 })),

    // XP5 (Final Stand)
    GameModeLevel(3, 26,  QList<int>({ 1, 2 })),
    GameModeLevel(3, 27,  QList<int>({ 1, 2 })),
    GameModeLevel(3, 28,  QList<int>({ 1, 2 })),
    GameModeLevel(3, 29,  QList<int>({ 1, 2 })),

    /* Obliteration */
    GameModeLevel(4, 0,   QList<int>({ 2, 1 })),
    GameModeLevel(4, 1,   QList<int>({ 2, 3 })),
    GameModeLevel(4, 2,   QList<int>({ 1, 3 })),
    GameModeLevel(4, 3,   QList<int>({ 2, 3 })),
    GameModeLevel(4, 4,   QList<int>({ 1, 3 })),
    GameModeLevel(4, 5,   QList<int>({ 1, 2 })),
    GameModeLevel(4, 6,   QList<int>({ 1, 3 })),
    GameModeLevel(4, 7,   QList<int>({ 1, 3 })),
    GameModeLevel(4, 8,   QList<int>({ 2, 3 })),
    GameModeLevel(4, 9,   QList<int>({ 1, 3 })),

    // XP1 (China Rising)
    GameModeLevel(4, 10,  QList<int>({ 1, 3 })),
    GameModeLevel(4, 11,  QList<int>({ 1, 3 })),
    GameModeLevel(4, 12,  QList<int>({ 1, 3 })),
    GameModeLevel(4, 13,  QList<int>({ 1, 3 })),

    // XP2 (Second Assault)
    GameModeLevel(4, 14,  QList<int>({ 1, 2 })),
    GameModeLevel(4, 15,  QList<int>({ 1, 2 })),
    GameModeLevel(4, 16,  QList<int>({ 1, 2 })),
    GameModeLevel(4, 17,  QList<int>({ 1, 2 })),

    // XP3 (Naval Strike)
    GameModeLevel(4, 18,  QList<int>({ 1, 2 })),
    GameModeLevel(4, 19,  QList<int>({ 1, 2 })),
    GameModeLevel(4, 20,  QList<int>({ 1, 2 })),
    GameModeLevel(4, 21,  QList<int>({ 1, 2 })),

    // XP4 (Dragon's Teeth)
    GameModeLevel(4, 22,  QList<int>({ 1, 3 })),
    GameModeLevel(4, 23,  QList<int>({ 1, 3 })),
    GameModeLevel(4, 24,  QList<int>({ 1, 3 })),
    GameModeLevel(4, 25,  QList<int>({ 1, 3 })),

    // XP5 (Final Stand)
    GameModeLevel(4, 26,  QList<int>({ 1, 2 })),
    GameModeLevel(4, 27,  QList<int>({ 1, 2 })),
    GameModeLevel(4, 28,  QList<int>({ 1, 2 })),
    GameModeLevel(4, 29,  QList<int>({ 1, 2 })),

    /* RushLarge0 */
    GameModeLevel(5, 0,   QList<int>({ 1, 3 })),
    GameModeLevel(5, 1,   QList<int>({ 1, 3 })),
    GameModeLevel(5, 2,   QList<int>({ 1, 3 })),
    GameModeLevel(5, 3,   QList<int>({ 1, 3 })),
    GameModeLevel(5, 4,   QList<int>({ 1, 3 })),
    GameModeLevel(5, 5,   QList<int>({ 1, 3 })),
    GameModeLevel(5, 6,   QList<int>({ 1, 3 })),
    GameModeLevel(5, 7,   QList<int>({ 1, 3 })),
    GameModeLevel(5, 8,   QList<int>({ 1, 3 })),
    GameModeLevel(5, 9,   QList<int>({ 1, 3 })),

    // XP1 (China Rising)
    GameModeLevel(5, 10,  QList<int>({ 1, 3 })),
    GameModeLevel(5, 11,  QList<int>({ 1, 3 })),
    GameModeLevel(5, 12,  QList<int>({ 1, 3 })),
    GameModeLevel(5, 13,  QList<int>({ 1, 3 })),

    // XP2 (Second Assault)
    GameModeLevel(5, 14,  QList<int>({ 1, 2 })),
    GameModeLevel(5, 15,  QList<int>({ 1, 2 })),
    GameModeLevel(5, 16,  QList<int>({ 1, 2 })),
    GameModeLevel(5, 17,  QList<int>({ 1, 2 })),

    // XP3 (Naval Strike)
    GameModeLevel(5, 18,  QList<int>({ 1, 2 })),
    GameModeLevel(5, 19,  QList<int>({ 1, 2 })),
    GameModeLevel(5, 20,  QList<int>({ 1, 2 })),
    GameModeLevel(5, 21,  QList<int>({ 1, 2 })),

    // XP4 (Dragon's Teeth)
    GameModeLevel(5, 22,  QList<int>({ 1, 3 })),
    GameModeLevel(5, 23,  QList<int>({ 1, 3 })),
    GameModeLevel(5, 24,  QList<int>({ 1, 3 })),
    GameModeLevel(5, 25,  QList<int>({ 1, 3 })),

    // XP5 (Final Stand)
    GameModeLevel(5, 26,  QList<int>({ 1, 2 })),
    GameModeLevel(5, 27,  QList<int>({ 1, 2 })),
    GameModeLevel(5, 28,  QList<int>({ 1, 2 })),
    GameModeLevel(5, 29,  QList<int>({ 1, 2 })),

    /* SquadDeathMatch0 */
    GameModeLevel(6, 0,   QList<int>({ 2, 1, 2, 1 })),
    GameModeLevel(6, 1,   QList<int>({ 2, 3, 2, 3 })),
    GameModeLevel(6, 2,   QList<int>({ 1, 3, 1, 3 })),
    GameModeLevel(6, 3,   QList<int>({ 2, 3, 2, 3 })),
    GameModeLevel(6, 4,   QList<int>({ 1, 3, 1, 3 })),
    GameModeLevel(6, 5,   QList<int>({ 1, 2, 1, 2 })),
    GameModeLevel(6, 6,   QList<int>({ 1, 3, 1, 3 })),
    GameModeLevel(6, 7,   QList<int>({ 1, 3, 1, 3 })),
    GameModeLevel(6, 8,   QList<int>({ 2, 3, 2, 3 })),
    GameModeLevel(6, 9,   QList<int>({ 1, 3, 1, 3 })),

    // XP1 (China Rising)
    GameModeLevel(6, 10,  QList<int>({ 1, 3, 1, 3 })),
    GameModeLevel(6, 11,  QList<int>({ 1, 3, 1, 3 })),
    GameModeLevel(6, 12,  QList<int>({ 1, 3, 1, 3 })),
    GameModeLevel(6, 13,  QList<int>({ 1, 3, 1, 3 })),

    // XP2 (Second Assault)
    GameModeLevel(6, 14,  QList<int>({ 1, 2, 1, 2 })),
    GameModeLevel(6, 15,  QList<int>({ 1, 2, 1, 2 })),
    GameModeLevel(6, 16,  QList<int>({ 1, 2, 1, 2 })),
    GameModeLevel(6, 17,  QList<int>({ 1, 2, 1, 2 })),

    // XP3 (Naval Strike)
    GameModeLevel(6, 18,  QList<int>({ 1, 2, 1, 2 })),
    GameModeLevel(6, 19,  QList<int>({ 1, 2, 1, 2 })),
    GameModeLevel(6, 20,  QList<int>({ 1, 2, 1, 2 })),
    GameModeLevel(6, 21,  QList<int>({ 1, 2, 1, 2 })),

    // XP4 (Dragon's Teeth)
    GameModeLevel(6, 22,  QList<int>({ 1, 3, 1, 3 })),
    GameModeLevel(6, 23,  QList<int>({ 1, 3, 1, 3 })),
    GameModeLevel(6, 24,  QList<int>({ 1, 3, 1, 3 })),
    GameModeLevel(6, 25,  QList<int>({ 1, 3, 1, 3 })),

    // XP5 (Final Stand)
    GameModeLevel(6, 26,  QList<int>({ 1, 2, 1, 2 })),
    GameModeLevel(6, 27,  QList<int>({ 1, 2, 1, 2 })),
    GameModeLevel(6, 28,  QList<int>({ 1, 2, 1, 2 })),
    GameModeLevel(6, 29,  QList<int>({ 1, 2, 1, 2 })),

    /* TeamDeathMatch0 */
    GameModeLevel(7, 0,   QList<int>({ 2, 1 })),
    GameModeLevel(7, 1,   QList<int>({ 2, 3 })),
    GameModeLevel(7, 2,   QList<int>({ 1, 3 })),
    GameModeLevel(7, 3,   QList<int>({ 2, 3 })),
    GameModeLevel(7, 4,   QList<int>({ 1, 3 })),
    GameModeLevel(7, 5,   QList<int>({ 1, 2 })),
    GameModeLevel(7, 6,   QList<int>({ 1, 3 })),
    GameModeLevel(7, 7,   QList<int>({ 1, 3 })),
    GameModeLevel(7, 8,   QList<int>({ 2, 3 })),
    GameModeLevel(7, 9,   QList<int>({ 1, 3 })),

    // XP1 (China Rising)
    GameModeLevel(7, 10,  QList<int>({ 1, 3 })),
    GameModeLevel(7, 11,  QList<int>({ 1, 3 })),
    GameModeLevel(7, 12,  QList<int>({ 1, 3 })),
    GameModeLevel(7, 13,  QList<int>({ 1, 3 })),

    // XP2 (Second Assault)
    GameModeLevel(7, 14,  QList<int>({ 1, 2 })),
    GameModeLevel(7, 15,  QList<int>({ 1, 2 })),
    GameModeLevel(7, 16,  QList<int>({ 1, 2 })),
    GameModeLevel(7, 17,  QList<int>({ 1, 2 })),

    // XP3 (Naval Strike)
    GameModeLevel(7, 18,  QList<int>({ 1, 2 })),
    GameModeLevel(7, 19,  QList<int>({ 1, 2 })),
    GameModeLevel(7, 20,  QList<int>({ 1, 2 })),
    GameModeLevel(7, 21,  QList<int>({ 1, 2 })),

    // XP4 (Dragon's Teeth)
    GameModeLevel(7, 22,  QList<int>({ 1, 3 })),
    GameModeLevel(7, 23,  QList<int>({ 1, 3 })),
    GameModeLevel(7, 24,  QList<int>({ 1, 3 })),
    GameModeLevel(7, 25,  QList<int>({ 1, 3 })),

    // XP5 (Final Stand)
    GameModeLevel(7, 26,  QList<int>({ 1, 2 })),
    GameModeLevel(7, 27,  QList<int>({ 1, 2 })),
    GameModeLevel(7, 28,  QList<int>({ 1, 2 })),
    GameModeLevel(7, 29,  QList<int>({ 1, 2 })),

    /* AirSuperiority0 */

    // XP1 (China Rising)
    GameModeLevel(8, 10,  QList<int>({ 1, 3 })),
    GameModeLevel(8, 11,  QList<int>({ 1, 3 })),
    GameModeLevel(8, 12,  QList<int>({ 1, 3 })),
    GameModeLevel(8, 13,  QList<int>({ 1, 3 })),

    /* CaptureTheFlag0 */

    // XP2 (Second Assault)
    GameModeLevel(9, 14,  QList<int>({ 1, 2 })),
    GameModeLevel(9, 15,  QList<int>({ 1, 2 })),
    GameModeLevel(9, 16,  QList<int>({ 1, 2 })),
    GameModeLevel(9, 17,  QList<int>({ 1, 2 })),

    // XP4 (Dragon's Teeth)
    GameModeLevel(9, 22,  QList<int>({ 1, 3 })),
    GameModeLevel(9, 23,  QList<int>({ 1, 3 })),
    GameModeLevel(9, 24,  QList<int>({ 1, 3 })),
    GameModeLevel(9, 25,  QList<int>({ 1, 3 })),

    // XP5 (Final Stand)
    GameModeLevel(9, 26,  QList<int>({ 1, 2 })),
    GameModeLevel(9, 27,  QList<int>({ 1, 2 })),
    GameModeLevel(9, 28,  QList<int>({ 1, 2 })),
    GameModeLevel(9, 29,  QList<int>({ 1, 2 })),

    /* Carrier Assault Small */

    // XP3 (Naval Strike)
    GameModeLevel(10, 18, QList<int>({ 1, 3 })),
    GameModeLevel(10, 19, QList<int>({ 1, 3 })),
    GameModeLevel(10, 20, QList<int>({ 1, 3 })),
    GameModeLevel(10, 21, QList<int>({ 1, 3 })),

    /* Carrier Assault Large */

    // XP3 (Naval Strike)
    GameModeLevel(11, 18, QList<int>({ 1, 3 })),
    GameModeLevel(11, 19, QList<int>({ 1, 3 })),
    GameModeLevel(11, 20, QList<int>({ 1, 3 })),
    GameModeLevel(11, 21, QList<int>({ 1, 3 })),

    /* Chainlink */

    // XP4 (Dragon's Teeth)
    GameModeLevel(12, 22, QList<int>({ 1, 3 })),
    GameModeLevel(12, 23, QList<int>({ 1, 3 })),
    GameModeLevel(12, 24, QList<int>({ 1, 3 })),
    GameModeLevel(12, 25, QList<int>({ 1, 3 }))
};
