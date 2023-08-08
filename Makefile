debug: clean buildDebug packDebug

buildDebug:
	builder winDebug.json

packDebug:
	if exist x64\Debug rmdir x64\Debug /s /q
	xcopy ".\source" ".\x64\Debug\inc\" /s /y
	cd x64\Debug\inc
	del /q /s .\.\x64\Debug\inc\*.cpp
	xcopy ".\lib" ".\x64\Debug\bin\" /s /y

release: clean buildRelease packRelease

buildRelease:
	builder winRelease.json

packRelease:
	if exist x64\Release rmdir x64\Release /s /q
	xcopy ".\source" ".\x64\Release\inc\" /s /y
	cd x64\Release\inc
	del /q /s .\.\x64\Release\inc\*.cpp
	xcopy ".\lib" ".\x64\Release\bin\" /s /y

clean:
	if exist .builder\obj rmdir .builder\obj /s /q
	if exist .builder\tmp rmdir .builder\tmp /s /q
	if exist lib\Hero.dll del lib\Hero.dll /s /q
