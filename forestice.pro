QT       += core gui
QT       += core gui multimedia
QT       += core gui multimedia multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += moc
CONFIG += c++17
CONFIG += resources_big
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    choose.cpp \
    dead.cpp \
    deadwater.cpp \
    door.cpp \
    ground.cpp \
    level1.cpp \
    level2.cpp \
    level3.cpp \
    main.cpp \
    mechanism.cpp \
    people.cpp \
    start.cpp \
    stone.cpp \
    stop.cpp \
    widget.cpp \
    win.cpp

HEADERS += \
    choose.h \
    dead.h \
    deadwater.h \
    door.h \
    ground.h \
    level1.h \
    level2.h \
    level3.h \
    mechanism.h \
    people.h \
    start.h \
    stone.h \
    stop.h \
    widget.h \
    win.h

FORMS += \
    choose.ui \
    dead.ui \
    level1.ui \
    level2.ui \
    level3.ui \
    start.ui \
    stop.ui \
    widget.ui \
    win.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourse.qrc
