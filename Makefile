build:
	g++ -w -std=c++14 -Wfatal-errors -m32 -static-libstdc++ \
	./src/*.cpp \
	-o "Gyro Engine.exe" \
	-I".\libsdl\SDL2\include" \
	-L".\libsdl\SDL2\lib" \
	-I".\lib\lua" \
	-L".\lib\lua" \
	-llua54 \
	-lmingw32 \
	-lSDL2main \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2_mixer \
	-lSDL2

clean:
	rm "Gyro Engine.exe"

run:
	"./Gyro Engine.exe"

