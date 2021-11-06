OS ?= windows

CC = gcc
TARGET = libhero
INCDIR = include
LIBDIR = lib
SOURCES = source/Hero/*.c source/TinyFileDialogs/*.c
OBJECTS = *.o
BUILDDIR = lib/windows


ifeq ($(OS),windows)
	RM = del /F /Q
	RMDIR = rmdir /S /Q
	MKDIR = mkdir
	COPY = xcopy /s /e
	IFEXIST = if exist
	LIBS = -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer -lsoil -lglew32 -lopengl32 -lglu32 -lm -lcomdlg32 -lole32
	EXTENSION = dll
else
	OS = linux
	RM = rm -rf
	RMDIR = rm -rf
	MKDIR = mkdir -p
	IFEXIST = 
	COPY = cp -R
	LIBS = -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSOIL -lGLEW -lGL -lGLU -lm
	EXTENSION = so
	BUILDDIR = lib/linux
endif

build: compile link clean

compile:
ifeq ($(OS),windows)
	$(CC) -g -D DEBUG -c -I$(INCDIR) -L$(LIBDIR)/$(OS) $(SOURCES) -fPIC $(LIBS)
else
	$(CC) -g -D DEBUG -c -I$(INCDIR) -L$(LIBDIR)/$(OS) $(SOURCES) -fPIC $(LIBS)
endif

link:
ifeq ($(OS),windows)
	$(CC) -g -D DEBUG -I$(INCDIR) -L$(LIBDIR)/$(OS) -o $(BUILDDIR)/$(TARGET).$(EXTENSION) $(OBJECTS) -shared $(LIBS)
else
	$(CC) -g -D DEBUG -I$(INCDIR) -L$(LIBDIR)/$(OS) -o $(BUILDDIR)/$(TARGET).$(EXTENSION) $(OBJECTS) -shared $(LIBS)
endif

clean:
ifeq ($(OS),windows)
	$(RM) *.o
else
	$(RM) *.o
endif