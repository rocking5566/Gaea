mkdir -p build/kernel
cd build/kernel
qmake ../../kernel/GaeaKernel.pro -r -spec  linux-g++
make
