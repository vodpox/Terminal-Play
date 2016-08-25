MINGW = i686-w64-mingw32-g++
CPP = $(shell find src/ -name *.cpp)
H = $(shell find src/ -name *.h)

all: build/libterminalplay.a

build/libterminalplay.a: $(CPP) $(H)
	mkdir -p obj/
	g++ -std=c++11 -static -c $(CPP) $(H)
	mv *.o ./obj/
	mkdir -p build/
	ar rcs build/libterminalplay.a obj/*
	rm -f src/*.gch

windows:
	mkdir -p obj/
	$(MINGW) -std=c++11 -static -c $(CPP) $(H)
	mv *.o ./obj/
	mkdir -p build/
	ar rcs build/libterminalplay.a obj/*
	rm -f src/*.gch

clean:
	rm -rf obj/
	rm -rf build/
