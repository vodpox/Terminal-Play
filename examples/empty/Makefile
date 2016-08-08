CC = g++
CPP = $(shell find . -name *.cpp)
H = $(shell find . -name *.h)
LDFLAGS = -I ../../src -L ../../build -lterminalplay

build: $(CPP) $(H)
	$(CC) -std=c++11 $(LDFLAGS) -c $(CPP) $(H)
	$(CC) *.o $(LDFLAGS) -o game
	

clean:
	rm -rf *.o
