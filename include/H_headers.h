#ifndef HERO_HEADERS_H_
#define HERO_HEADERS_H_

#ifdef __linux__
  #include<SDL2/SDL.h>
  #include<GL/glew.h>
  #include<SOIL/SOIL.h>
  #include<SDL2/SDL_opengl.h>
  #include<SDL2/SDL_ttf.h>
  #include<SDL2/SDL_mixer.h>
  #include<GL/glu.h>
  #include<GL/gl.h>
#else
  #include<SDL\SDL.h>
  #include<GL\glew.h>
  #include<GL\glu.h>
  #include<GL\gl.h>
  #include<SOIL\SOIL.h>
  #include<SDL\SDL_opengl.h>
  #include<SDL\SDL_ttf.h>
  #include<SDL\SDL_mixer.h>
#endif

#endif