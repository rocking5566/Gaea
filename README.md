# Gaea

    Gaea is a cross platform streaming player
  - We use LibVLC to get RTSP stream and decode the video
  - Give an example of how to convert the image frame to the OpenCV Mat format to apply computer vision algorithm.
  - We use OpenGL to acclerate rendering the video on Qt windows GUI.

## Dependency Library
  - C++ 11
  - QT 5.7.1
  - LibVlc 2.2.2
  - OpenCV 2.4.9
  
> You can downlaod the include header and binary(win64) [here](https://drive.google.com/drive/folders/0B1Mq7kkwjPxLWWZMVzgyQTMxdHc?usp=sharing).

## Windows Development Environment
  - Visual studio 2013 with x64 tool chain
  - Visual Studio Add-in 2.0.0 for Qt5 MSVC 2013

## Ubuntu Development Environment
  - Ubuntu 16.0.04
  - Install QT 5.7.1 and Qt Creator. (https://wiki.qt.io/Install_Qt_5_on_Ubuntu)
  - Install libvlc-dev on Ubuntu. (http://www.rukspot.com/How_to_install_LibVLC_on_Ubuntu.html)
  - Install OpenCV on Ubuntu. (http://docs.opencv.org/2.4/doc/tutorials/introduction/linux_install/linux_install.html)