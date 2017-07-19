KERNEL_PATH = ../kernel

SOURCES += $${KERNEL_PATH}/stream/PlayerCtrl.cpp \
           $${KERNEL_PATH}/stream/RtspHelper.cpp \
           $${KERNEL_PATH}/stream/StreamSession.cpp \
           $${KERNEL_PATH}/util/WorkerThread.cpp

HEADERS += $${KERNEL_PATH}/stream/PlayerCtrl.h \
           $${KERNEL_PATH}/stream/RtspHelper.h \
           $${KERNEL_PATH}/stream/StreamSession.h \
           $${KERNEL_PATH}/util/Util.h \
           $${KERNEL_PATH}/util/WorkerThread.h
