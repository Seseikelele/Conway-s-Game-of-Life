all: wholeApp

wholeApp: Source.o Life.o
	g++ Source.o Life.o -o GameOfLife
	rm Source.o Life.o

Source.o: Source.cpp
	g++ -c Source.cpp

Life.o: Life.cpp
	g++ -c Life.cpp

clean:
	rm -f GameOfLife Source.o Life.o
