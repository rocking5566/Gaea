COMMON_PATH = $${PWD}/../Common

INCLUDEPATH += $${COMMON_PATH} \
               $${OPENCV_PATH}/include \
               $${PWD}/src \
               $${PWD}/src/Component \
               $${STREAM_ENGINE_PATH}/include \
               $${VLC_PATH}/include

SOURCES += $${COMMON_PATH}/RenderWidget.cpp \
           ./src/Component/Tab/TabEntity.cpp \
           ./src/Component/Tab/TabWidget.cpp \
           ./src/Device/ConfigDeviceWidget.cpp \
           ./src/Device/DeviceModel.cpp \
           ./src/FaceConfig/MemberModel.cpp \
           ./src/FaceConfig/RegisterFaceWidget.cpp \
           ./src/LiveView/FilmView.cpp \
           ./src/LiveView/LiveViewWidget.cpp \
           ./src/HomeWindow.cpp \
           ./src/SysConfig/SysConfigWidget.cpp \
           ./src/main.cpp

HEADERS += $${COMMON_PATH}/RenderWidget.h \
           ./src/Component/Tab/TabEntity.h \
           ./src/Component/Tab/TabWidget.h \
           ./src/Device/ConfigDeviceWidget.h \
           ./src/Device/DeviceModel.h \
           ./src/FaceConfig/MemberModel.h \
           ./src/FaceConfig/RegisterFaceWidget.h \
           ./src/LiveView/FilmView.h \
           ./src/LiveView/LiveViewWidget.h \
           ./src/SysConfig/SysConfigWidget.h \
           ./src/HomeWindow.h

FORMS   += ./UI/ConfigDeviceWidget.ui \
           ./UI/HomeWindow.ui \
           ./UI/LiveViewWidget.ui \
           ./UI/RegisterFaceWidget.ui \
           ./UI/SysConfigWidget.ui
