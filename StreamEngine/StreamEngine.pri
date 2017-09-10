STREAM_ENGINE_PATH = $${PWD}
INCLUDEPATH += $${VLC_PATH}/include \
               $${OPENCV_PATH}/include \
               $${STREAM_ENGINE_PATH}/include \
               $${STREAM_ENGINE_PATH}/src


SOURCES += $${STREAM_ENGINE_PATH}/src/Stream/PlayerCtrl.cpp \
           $${STREAM_ENGINE_PATH}/src/Stream/RtspStream.cpp \
           $${STREAM_ENGINE_PATH}/src/Stream/StreamClient.cpp \
           $${STREAM_ENGINE_PATH}/src/Stream/StreamCtrl.cpp \
           $${STREAM_ENGINE_PATH}/src/Stream/WebCamStream.cpp \
           $${STREAM_ENGINE_PATH}/src/MemoryManagement/BufPoolMgr.cpp \
           $${STREAM_ENGINE_PATH}/src/Pattern/WorkerThread.cpp \
           $${STREAM_ENGINE_PATH}/src/DataStructure/ImageAdaptor.cpp

HEADERS += $${STREAM_ENGINE_PATH}/include/StreamEngineTypes.h \
           $${STREAM_ENGINE_PATH}/include/PlayerCtrl.h \
           $${STREAM_ENGINE_PATH}/include/Util.h \
           $${STREAM_ENGINE_PATH}/include/ImageAdaptor.h \
           $${STREAM_ENGINE_PATH}/src/MemoryManagement/BufPoolMgr.h \
           $${STREAM_ENGINE_PATH}/include/WorkerThread.h \
           $${STREAM_ENGINE_PATH}/src/Stream/RtspStream.h \
           $${STREAM_ENGINE_PATH}/src/Stream/StreamClient.h \
           $${STREAM_ENGINE_PATH}/src/Stream/StreamCtrl.h \
           $${STREAM_ENGINE_PATH}/src/Stream/WebCamStream.h
           
