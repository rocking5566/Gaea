INCLUDEPATH += $${VLC_PATH}/include \
               $${OPENCV_PATH}/include \
               $${STREAM_ENGINE_PATH}/include \
               $${PWD}/src

SOURCES += ./src/ConnectionListDock.cpp \
           ./src/main.cpp \
           ./src/HomeWindow.cpp \
           ./src/PlayerWidget.cpp \
           ./src/RenderWidget.cpp

HEADERS += ./src/ConnectionListDock.h \
           ./src/HomeWindow.h \
           ./src/PlayerWidget.h \
           ./src/RenderWidget.h

FORMS   += ./UI/ConnectionListWidget.ui \
           ./UI/HomeWindow.ui \
           ./UI/PlayerWidget.ui