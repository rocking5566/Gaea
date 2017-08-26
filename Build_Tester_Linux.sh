mkdir -p build/StreamEngine
cd build/StreamEngine
/usr/bin/qmake ../../Tester/Tester.pro -r -spec  linux-g++
make
