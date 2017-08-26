mkdir -p build/Tester
cd build/Tester
/usr/bin/qmake ../../Tester/Tester.pro -r -spec  linux-g++
make
