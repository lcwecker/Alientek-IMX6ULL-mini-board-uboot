#!/bin/bash
set -e

init_clangd()
{
    rm -rf .cache
    rm -f compile_commands.json
    make V=1 -n | compiledb -v
}

export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabihf-
make distclean
make mx6ull_alientek_nand_defconfig
#init_clangd
make -j"$(nproc)"