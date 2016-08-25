CC = g++
MINGW = i686-w64-mingw32-g++
CPP = $(shell find . -name *.cpp)
H = $(shell find . -name *.h)
LDFLAGS = -I ../../src -L ../../build -lterminalplay

build: $(CPP) $(H)
	$(CC) -std=c++11 -static $(LDFLAGS) -c $(CPP) $(H)
	$(CC) *.o $(LDFLAGS) -o game -static

windows: $(CPP) $(H)
	$(MINGW) -std=c++11 -static $(LDFLAGS) -c $(CPP) $(H)
	$(MINGW) *.o $(LDFLAGS) -o game.exe -static
	

clean:
	rm -rf *.o
