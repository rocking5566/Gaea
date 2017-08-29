mkdir -p build/StreamEngine
cd build/StreamEngine

# Stream Engine SDK
/usr/bin/qmake ../../StreamEngine/StreamEngine.pro -r -spec  linux-g++
make

# Stream Engine Tester
/usr/bin/qmake ../../StreamEngine/Tester/Tester.pro -r -spec  linux-g++
make

cd ../..
