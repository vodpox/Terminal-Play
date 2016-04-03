CPP = $(shell find src/ -name *.cpp)
H = $(shell find src/ -name *.h)

all: build/libterminalplay.a

build/libterminalplay.a: $(CPP) $(H)
	mkdir -p obj/
	g++ -std=c++11 -c $(CPP) $(H)
	mv *.o ./obj/
	mkdir -p build/
	ar rcs build/libterminalplay.a obj/*

clean:
	rm -rf obj/
	rm -rf build/
