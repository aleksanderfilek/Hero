@echo off
echo Compiling Hero Library
gcc -std=c99 -D DEBUG -c -I../include/ ../source/*.c -fPIC -lm
gcc -std=c99 -D DEBUG -o libhero.dll *.o -shared -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer -lsoil -lglew32 -lopengl32 -lglu32 -lm

echo Compiling Game
gcc -std=c99 -D DEBUG -L. -I../include/ -o main.exe main.c -lhero -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer -lsoil -lglew32 -lopengl32 -lglu32 -lm

del *.o