call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86_amd64
IF NOT EXIST build mkdir build
IF NOT EXIST build\Tester mkdir build\Tester

cd build\Tester
qmake.exe -spec win32-msvc2013 "CONFIG += x86_64" -r ../../Tester/Tester.pro
nmake
