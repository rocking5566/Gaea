call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86_amd64
IF NOT EXIST build mkdir build
IF NOT EXIST build\StreamEngine mkdir build\StreamEngine

cd build\StreamEngine

rem Stream Engine SDK
qmake.exe -spec win32-msvc2013 "CONFIG += x86_64" -r ../../StreamEngine/StreamEngine.pro
nmake

rem Stream Engine Tester
qmake.exe -spec win32-msvc2013 "CONFIG += x86_64" -r ../../StreamEngine/Tester/Tester.pro
nmake
