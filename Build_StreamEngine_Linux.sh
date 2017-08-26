mkdir -p build/StreamEngine
cd build/StreamEngine
/usr/bin/qmake ../../StreamEngine/StreamEngine.pro -r -spec  linux-g++
make
