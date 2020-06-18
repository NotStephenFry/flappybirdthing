QT += core gui widgets

TARGET = app
TEMPLATE = app
CONFIG = debug
DESTDIR = ./build
OBJECTS_DIR = ./temp

LIBS += -lSDL2 -lSDL2_image

HEADERS += inc/Game.h inc/Bird.h inc/Pipe.h inc/Actor.h inc/TextureManager.h
SOURCES += src/Game.cpp src/Bird.cpp src/Pipe.cpp src/Actor.cpp src/TextureManager.cpp src/main.cpp
