INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += frostbite/FrostbiteConnection.h \
    frostbite/FrostbiteRconPacket.h \
    frostbite/FrostbiteRconWord.h \
    frostbite/FrostbiteCommandHandler.h \
    frostbite/FrostbiteGame.h \
    frostbite/FrostbiteUtils.h \
    frostbite/LevelEntry.h \
    frostbite/LevelDictionary.h \
    frostbite/GameModeEntry.h \
    frostbite/PlayerSubset.h \
    frostbite/MapListEntry.h \
    frostbite/BanListEntry.h \
    frostbite/ServerInfo.h \
    frostbite/TimeEntry.h \
    frostbite/OnlineState.h \
    frostbite/TeamScores.h

SOURCES += frostbite/FrostbiteConnection.cpp \
    frostbite/FrostbiteRconPacket.cpp \
    frostbite/FrostbiteRconWord.cpp \
    frostbite/FrostbiteCommandHandler.cpp \
    frostbite/FrostbiteGame.cpp \
    frostbite/FrostbiteUtils.cpp \
    frostbite/LevelDictionary.cpp
