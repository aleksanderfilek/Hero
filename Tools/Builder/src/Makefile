current_dir = $(shell pwd)

OS ?= win

ifeq ($(OS), win)
	RM = del /F /Q
	RMDIR = rmdir /S /Q
	DIR = win
	RUNTIME = win-x64
else
	RM = rm -rf
	RMDIR = rm -rf
	DIR = linux
	RUNTIME = ubuntu.20.10-x64
endif

run:
	./bin/Debug/net6.0/Builder ./../../../Engine/

publish:
	dotnet publish -c release -r $(RUNTIME) --no-self-contained -o ./../bin/$(DIR)


build:
	dotnet build

clean:
	$(RMDIR) ./bin
	$(RMDIR) ./obj
	$(RMDIR) ./../bin/$(DIR)