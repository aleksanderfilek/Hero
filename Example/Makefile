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
	./bin/Example$(EXT)

update: download build run
	
download:
	$(COPY) ..\Engine\inc inc\Hero /s /e
	$(COPY) ..\Engine\lib\libhero.dll bin /s /e