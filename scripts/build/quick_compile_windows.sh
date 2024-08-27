#!/bin/bash


nasm -f win64 cpuidIsSupported.asm -o cpuidIsSupported.o

gcc -m64 main.c cpu_information.c cpu_interface.c cpuidIsSupported.o -o build/bin/cpu_analyzer.exe