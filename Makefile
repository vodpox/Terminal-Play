all: build/libterminalplay.a

build/libterminalplay.a: obj/Game.o obj/Graphics.o
	mkdir -p build/
	ar rcs build/libterminalplay.a obj/*

obj/Game.o: src/Game.cpp src/Game.h
	mkdir -p obj/
	g++ -std=c++11 -c src/Game.cpp -o obj/Game.o

obj/Graphics.o: src/Graphics.cpp src/Graphics.h
	mkdir -p obj/
	g++ -std=c++11 -c src/Graphics.cpp -o obj/Graphics.o

clean:
	rm -rf obj/
	rm -rf build/