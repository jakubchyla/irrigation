#! /usr/bin/env sh

openocd -f interface/stlink.cfg -f target/stm32l4x.cfg -c "program build/Debug/bin/irrigation.elf verify reset exit"
