KERNEL_PATH = ../kernel

SOURCES += $${KERNEL_PATH}/stream/PlayerCtrl.cpp \
           $${KERNEL_PATH}/stream/RtspHelper.cpp \
           $${KERNEL_PATH}/stream/StreamCtrl.cpp \
           $${KERNEL_PATH}/util/BufPoolMgr.cpp \
           $${KERNEL_PATH}/util/WorkerThread.cpp

HEADERS += $${KERNEL_PATH}/def/KernelTypes.h \
           $${KERNEL_PATH}/stream/PlayerCtrl.h \
           $${KERNEL_PATH}/stream/RtspHelper.h \
           $${KERNEL_PATH}/stream/StreamCtrl.h \
           $${KERNEL_PATH}/util/BufPoolMgr.h \
           $${KERNEL_PATH}/util/Util.h \
           $${KERNEL_PATH}/util/WorkerThread.h
