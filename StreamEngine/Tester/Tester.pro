TARGET = Tester
HOME_PATH = $${PWD}/../..
VLC_PATH = $${PWD}/../../packages/libvlc-2.2.2
OPENCV_PATH = $${PWD}/../../packages/opencv249
STREAM_ENGINE_PATH = $${PWD}/..

# Project setting
QT += core gui opengl network widgets
CONFIG -= flat
CONFIG += c++11

# Include file(s) (Include the pri file generated by VS-Addin.)
include(Tester.pri)

win32 {
    QMAKE_CXXFLAGS += /Zi
    contains(QMAKE_TARGET.arch, x86_64) {
        QMAKE_LFLAGS += /MACHINE:X64
        LIBS += -L$${VLC_PATH}/lib -llibvlc.x64 -llibvlccore.x64
        
        CONFIG(debug, debug|release) {
            DESTDIR = $${HOME_PATH}/build/x64/Debug
            LIBS += -L$${OPENCV_PATH}/lib -lopencv_core249d -lopencv_highgui249d
            LIBS += -L$${HOME_PATH}/build/x64/Debug -lStreamEngine
            QMAKE_LFLAGS_WINDOWS += /LARGEADDRESSAWARE
        }
        else {
            DESTDIR = $${HOME_PATH}/build/x64/Release
            LIBS += -L$${OPENCV_PATH}/lib -lopencv_core249 -lopencv_highgui249
            LIBS += -L$${HOME_PATH}/build/x64/Release -lStreamEngine
            QMAKE_LFLAGS_WINDOWS += /debug /opt:ref /MAP /MAPINFO:EXPORTS /LARGEADDRESSAWARE
        }
    }
    else {
        QMAKE_LFLAGS += /MACHINE:X86
        #Require x86 lib
        #LIBS +=
		CONFIG(debug, debug|release) {
            DESTDIR = $${HOME_PATH}/build/Win32/Debug
            QMAKE_LFLAGS_WINDOWS += /LARGEADDRESSAWARE
        }
        else {
            DESTDIR = $${HOME_PATH}/build/Win32/Release
            QMAKE_LFLAGS_WINDOWS += /debug /opt:ref /MAP /MAPINFO:EXPORTS /LARGEADDRESSAWARE
        }
    }
}

linux-g++ {
    CONFIG(debug, debug|release) {
        DESTDIR = $${HOME_PATH}/build/Debug
    }
    else {
        DESTDIR = $${HOME_PATH}/build/Release
    }

    LIBS += -L/usr/lib/ -lvlc
    LIBS += -L/usr/local/lib -lopencv_highgui -lopencv_core -lopencv_imgproc
    LIBS += -L$${DESTDIR} -lStreamEngine
}
