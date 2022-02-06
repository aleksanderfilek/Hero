OS := win

ifeq ($(OS), win)
	DIR = win
	EXT = .exe
	COPY = xcopy
else
	DIR = linux
	EXT = 
	COPY = cp -R
endif

build: 
	./../Tools/Builder/bin/$(DIR)/Builder$(EXT)

run:
	./bin/Example.exe

update: download build run
	
download:
	$(COPY) ../Engine/inc inc/Hero
	$(COPY) ../Engine/lib/libhero.so bin