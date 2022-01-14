OS := win

ifeq ($(OS), win)
	DIR = win
	EXT = .exe
else
	DIR = linux
	EXT = 
endif

build: 
	./../Tools/Builder/bin/$(DIR)/Builder$(EXT)

run:
	./bin/Editor.exe

