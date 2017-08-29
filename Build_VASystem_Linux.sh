sh Build_StreamEngine_Linux.sh

mkdir -p build/VASystem
cd build/VASystem

/usr/bin/qmake ../../VASystem/VASystem.pro -r -spec  linux-g++
make
