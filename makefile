CC=g++
LIBS =

all: floats.cpp utils.h
	$(CC) floats.cpp -o floats.o $(LIBS)

clean:
	rm -f floats.o
