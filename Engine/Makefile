CC := g++
CFLAGS := -g -DDEBUG -DHERO_DEBUG

all: compile link

compile:
	SRCDIR := Engine/src/Core
	SOURCES := $(shell find $(SRCDIR) -type f -name *.cpp)
	OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o))


link: