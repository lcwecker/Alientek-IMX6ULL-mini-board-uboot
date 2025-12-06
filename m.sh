#!/bin/bash

export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabihf-
make distclean
make mx6ull_14x14_evk_nand_defconfig
# make V=1 | compiledb
make -j11