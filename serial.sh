#! /usr/bin/env sh

if [ "$1" = "" ]; then
    printf "no tty device specified\n"
    exit 1
fi
picocom -b 9600 -d 8 -p n "$1"
