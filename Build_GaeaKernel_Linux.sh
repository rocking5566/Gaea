mkdir -p build/kernel
cd build/kernel
/usr/bin/qmake ../../kernel/GaeaKernel.pro -r -spec  linux-g++
make
