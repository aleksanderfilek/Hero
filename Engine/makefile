all: build package

build:
	if exist .builder rmdir .builder /s /q
	if exist Hero\lib\libhero.dll del Hero\lib\libhero.dll
	builder winConfig.json

package:
	if exist Hero\inc\Hero rmdir Hero\inc\Hero /s /q
	xcopy ".\source" ".\Hero\inc\Hero\" /s /y
	cd Hero/inc/Hero
	del /q /s .\Hero\inc\Hero\*.cpp
	7z a -tzip Hero.zip Hero