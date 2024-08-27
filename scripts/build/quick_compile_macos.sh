#!/bin/bash

nasm -f macho64 src/cpuidIsSupported.asm -o build/cpuidIsSupported.o

gcc -m64 main.c src/cpu_interface.c build/cpuidIsSupported.o -o build/bin/cpu_analyzer