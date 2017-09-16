COMMON_PATH = $${PWD}/../../Common

INCLUDEPATH += $${COMMON_PATH} \
               $${OPENCV_PATH}/include \
               $${PWD}/src \
               $${STREAM_ENGINE_PATH}/include \
               $${VLC_PATH}/include

SOURCES += $${COMMON_PATH}/RenderWidget.cpp \
           ./src/ConnectionListDock.cpp \
           ./src/main.cpp \
           ./src/HomeWindow.cpp \
           ./src/PlayerWidget.cpp

HEADERS += ./$${COMMON_PATH}/RenderWidget.h \
           ./src/ConnectionListDock.h \
           ./src/HomeWindow.h \
           ./src/PlayerWidget.h

FORMS   += ./UI/ConnectionListWidget.ui \
           ./UI/HomeWindow.ui \
           ./UI/PlayerWidget.ui