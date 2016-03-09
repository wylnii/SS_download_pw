QT += core network
QT -= gui

CONFIG += c++11

TARGET = download_password
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    downloader.cpp

HEADERS += \
    downloader.h

#RC_FILE += \
#    my.rc
RC_ICONS = myico.ico
