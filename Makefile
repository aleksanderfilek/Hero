engine:
	g++ -c -DEBUG -DHERO_DEBUG -IEngine/inc -IEngine/ThirdParty Engine/src/Core/*.cpp -fPIC
	g++ -c -DEBUG -DHERO_DEBUG -IEngine/inc -IEngine/ThirdParty Engine/src/Systems/*.cpp -fPIC
	g++ -c -DEBUG -DHERO_DEBUG -IEngine/inc -IEngine/ThirdParty Engine/src/TinyFileDialogs/*.c -fPIC
	g++ -DEBUG -DHERO_DEBUG -shared *.o -o libHerod.so -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSOIL -lGLEW -lGL -lGLU -lm
	g++ -DEBUG -DHERO_DEBUG -IEngine -L. main.cpp -lHerod