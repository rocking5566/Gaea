KERNEL_PATH = ../kernel

SOURCES += $${KERNEL_PATH}/stream/PlayerCtrl.cpp \
           $${KERNEL_PATH}/stream/RtspStream.cpp \
           $${KERNEL_PATH}/stream/StreamClient.cpp \
           $${KERNEL_PATH}/stream/StreamCtrl.cpp \
           $${KERNEL_PATH}/stream/WebCamStream.cpp \
           $${KERNEL_PATH}/util/BufPoolMgr.cpp \
           $${KERNEL_PATH}/util/WorkerThread.cpp \
           $${KERNEL_PATH}/VideoFrame.cpp

HEADERS += $${KERNEL_PATH}/def/KernelTypes.h \
           $${KERNEL_PATH}/stream/PlayerCtrl.h \
           $${KERNEL_PATH}/stream/RtspStream.h \
           $${KERNEL_PATH}/stream/StreamClient.h \
           $${KERNEL_PATH}/stream/StreamCtrl.h \
           $${KERNEL_PATH}/stream/WebCamStream.h \
           $${KERNEL_PATH}/util/BufPoolMgr.h \
           $${KERNEL_PATH}/util/Util.h \
           $${KERNEL_PATH}/util/WorkerThread.h \
           $${KERNEL_PATH}/VideoFrame.h
