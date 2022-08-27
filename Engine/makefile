all: build package

build:
	builder winConfig.json

package:
	xcopy ".\source" ".\Hero\inc\Hero\" /s /y
	cd Hero/inc/Hero
	del /q /s .\Hero\inc\Hero\*.cpp
	7z a -tzip Hero.zip Hero