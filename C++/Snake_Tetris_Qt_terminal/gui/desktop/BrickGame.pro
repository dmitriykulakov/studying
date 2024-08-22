QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
../../brick_game/snake/controller_s.cpp \
../../brick_game/snake/model_s.cpp \
    ../../brick_game/tetris/model.c \
    main.cpp \
    gameview.cpp

HEADERS += \
../../brick_game/main.h \
../../brick_game/snake/controller_s.h \
../../brick_game/snake/model_s.h \
 ../../brick_game/tetris/model.h \
    gameview.h

FORMS += \
    gameview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
