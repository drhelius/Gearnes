QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += opengl

TARGET = Gearnes
TEMPLATE = app

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/lib

LIBS += -L/usr/local/lib -lSDL2main -lSDL2 -lGLEW -lGLU -lGL

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    ../../qt-shared/about.cpp \
    ../../qt-shared/emulator.cpp \
    ../../qt-shared/gl_frame.cpp \
    ../../qt-shared/input_settings.cpp \
    ../../qt-shared/main_window.cpp \
    ../../qt-shared/main.cpp \
    ../../qt-shared/render_thread.cpp \
    ../../qt-shared/sound_settings.cpp \
    ../../qt-shared/video_settings.cpp \
    ../../../src/audio.cpp \
    ../../../src/cartridge.cpp \
    ../../../src/input.cpp \
    ../../../src/video.cpp \
    ../../../src/miniz/miniz.c \
    ../../../src/gearnes_core.cpp \
    ../../../src/G6502/g6502_core.cpp \
    ../../../src/G6502/g6502_opcodes.cpp \
    ../../../src/mapper.cpp \
    ../../../src/memory.cpp

HEADERS  += \
    ../../qt-shared/about.h \
    ../../qt-shared/emulator.h \
    ../../qt-shared/gl_frame.h \
    ../../qt-shared/input_settings.h \
    ../../qt-shared/main_window.h \
    ../../qt-shared/render_thread.h \
    ../../qt-shared/sound_settings.h \
    ../../qt-shared/video_settings.h \
    ../../../src/audio.h \
    ../../../src/cartridge.h \
    ../../../src/definitions.h \
    ../../../src/input.h \
    ../../../src/video.h \
    ../../../src/gearnes.h \
    ../../../src/gearnes_core.h \
    ../../../src/G6502/g6502_core.h \
    ../../../src/G6502/g6502_core_inl.h \
    ../../../src/G6502/g6502_definitions.h \
    ../../../src/G6502/g6502_eight_bit_register.h \
    ../../../src/G6502/g6502_memory_interface.h \
    ../../../src/G6502/g6502_sixteen_bit_register.h \
    ../../../src/G6502/g6502_opcode_names.h \
    ../../../src/G6502/g6502_opcode_timing.h \
    ../../../src/mapper.h \
    ../../../src/memory.h \
    ../../../src/memory_inline.h

FORMS += \
    ../../qt-shared/About.ui \
    ../../qt-shared/InputSettings.ui \
    ../../qt-shared/MainWindow.ui \
    ../../qt-shared/SoundSettings.ui \
    ../../qt-shared/VideoSettings.ui
