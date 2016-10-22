INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/Minecraft.h \
    $$PWD/MinecraftConnection.h \
    $$PWD/MinecraftRconPacketType.h \
    $$PWD/MinecraftRconPacket.h \
    $$PWD/MinecraftWidget.h \
    $$PWD/MinecraftCommandHandler.h \
    $$PWD/MinecraftRconCommandType.h

SOURCES += $$PWD/Minecraft.cpp \
    $$PWD/MinecraftConnection.cpp \
    $$PWD/MinecraftRconPacket.cpp \
    $$PWD/MinecraftWidget.cpp \
    $$PWD/MinecraftCommandHandler.cpp

FORMS += $$PWD/MinecraftWidget.ui

RESOURCES += $$PWD/Minecraft.qrc
