#!/bin/sh
gcc -std=c99 -D DEBUG -c -Iinclude/ source/*.c -fPIC -lm
gcc -std=c99 -D DEBUG -o libhero.so *.o -shared -lm
gcc -std=c99 -D DEBUG -L. -Iinclude/ main.c -lhero -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSOIL -lGLEW -lGL -lGLU -lm

unset LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/home/username/Dokumenty/projekty/HeroCore:$LD_LIBRARY_PATH

rm *.o