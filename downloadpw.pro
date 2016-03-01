QT += core network
QT -= gui

CONFIG += c++11

TARGET = downloadpw
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    downloader.cpp

HEADERS += \
    downloader.h
