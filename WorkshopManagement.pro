

greaterThan(QT_MAJOR_VERSION, 4):
QT       += core gui

QT += widgets
QT += sql

QT += printsupport

QT += charts
QT += network
QT += texttospeech
QT += serialport

CONFIG += c++11
CONFIG += console
CONFIG += openssl
# OpenSSL library path
LIBS += -LC:/OpenSSL-Win32/lib

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    client.cpp \
    clientmanagement.cpp \
    employee.cpp \
    employee_management.cpp \
    equipment.cpp \
    equipment_managment.cpp \
    main.cpp \
    WorkshopManagement.cpp \
    connection.cpp \
    menu.cpp \
    room.cpp \
    room_management.cpp \
    projectsmanagement.cpp \
    project.cpp \
    sms.cpp \
    src/emailaddress.cpp \
    src/mimeattachment.cpp \
    src/mimecontentformatter.cpp \
    src/mimefile.cpp \
    src/mimehtml.cpp \
    src/mimeinlinefile.cpp \
    src/mimemessage.cpp \
    src/mimemultipart.cpp \
    src/mimepart.cpp \
    src/mimetext.cpp \
    src/quotedprintable.cpp \
    src/smtpclient.cpp \
    workshop.cpp


HEADERS += \
    WorkshopManagement.h \
    arduino.h \
    client.h \
    clientmanagement.h \
    connection.h \
    employee.h \
    employee_management.h \
    equipment.h \
    equipment_managment.h \
    menu.h \
    room.h \
    room_management.h \
    projectsmanagement.h \
    project.h \
    sms.h \
    src/SmtpMime \
    src/emailaddress.h \
    src/mimeattachment.h \
    src/mimecontentformatter.h \
    src/mimefile.h \
    src/mimehtml.h \
    src/mimeinlinefile.h \
    src/mimemessage.h \
    src/mimemultipart.h \
    src/mimepart.h \
    src/mimetext.h \
    src/quotedprintable.h \
    src/smtpclient.h \
    src/smtpexports.h \
    workshop.h

FORMS += \
    WorkshopManagement.ui \
    clientmanagement.ui \
    employee_management.ui \
    equipment_managment.ui \
    room_management.ui \
    projectsmanagement.ui \
    menu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

#DISTFILES += \
    #../../../../../../../../../Programs/OpenSSL-Win64/bin/libeay32.dll \
    #../../../../../../../../../Programs/OpenSSL-Win64/bin/ssleay32.dll \
    #src/CMakeLists.txt*/

