#!/bin/sh
echo Compiling Hero Library
gcc -std=c99 -D DEBUG -c -I../include/ ../source/*.c -fPIC -lm
gcc -std=c99 -D DEBUG -o libhero.so *.o -shared -lm

echo Compiling Game
gcc -std=c99 -D DEBUG -L. -I../include/ -o main.out main.c -lhero -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSOIL -lGLEW -lGL -lGLU -lm

unset LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/home/username/Dokumenty/projekty/HeroCore:$LD_LIBRARY_PATH

rm *.o