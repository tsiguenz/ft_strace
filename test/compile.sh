#!/bin/bash

MAINS=(
	"basic.c"
	"signals.c"
	"no_signal_handler.c"
)

for main in "${MAINS[@]}";do
	gcc -m64 "$main" -o "${main%%.*}"_64
	#gcc -m32 "$main" -o "${main%%.*}"_32
done
