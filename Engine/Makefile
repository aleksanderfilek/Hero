current_dir = $(bash pwd)

OS ?= win

ifeq ($(OS), win)
	DIR = win
	EXT = .exe
else
	DIR = linux
	EXT = 
endif

all: 
	./../Tools/Builder/bin/$(DIR)/Builder$(EXT) .
