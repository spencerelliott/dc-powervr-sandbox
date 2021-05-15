#!/bin/bash

sh-elf-objcopy -R .stack -O binary $1.elf $1.bin
${KOS_BASE}/utils/scramble/scramble $1.bin cd_root/1ST_READ.bin
${KOS_BASE}/utils/makeip/src/makeip -vf IP.BIN
cd cd_root
../makedisc ../$1.cdi . ../IP.BIN $1
cd ..

