mkdir -p build/tester
cd build/tester
/usr/bin/qmake ../../GaeaPlayer/GaeaPlayer.pro -r -spec  linux-g++
make
