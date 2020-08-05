#!/bin/bash

PROJECT="PVRTest"

source /opt/toolchains/dc/kos/environ.sh

cd src
if make; then
    cd ../bin
    lxdream --gdb-sh=9999 -e ${PROJECT}.elf
fi