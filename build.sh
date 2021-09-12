#!/bin/sh
gcc -std=c99 -D DEBUG -c -Iinclude/ source/*.c -fPIC
gcc -std=c99 -D DEBUG -o libhero.so *.o -shared
gcc -std=c99 -D DEBUG -L. -Iinclude/ main.c -lhero -lSDL2main -lSDL2 -lSDL2_ttf -lSOIL -lGLEW -lGL -lGLU

unset LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/home/username/Dokumenty/projekty/HeroCore:$LD_LIBRARY_PATH

rm *.o