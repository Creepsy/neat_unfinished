CLFAGS=-g -Wall
LDFLAGS=

build/test: build/test.o build/libneat.a
	g++ build/test.o -o build/test -Lbuild -lneat $(LDFLAGS)

build/test.o: src/test.cpp
	g++ -c src/test.cpp -o build/test.o $(CFLAGS) 

build/libneat.a: build/lib.o build/genome.o
	ar crf build/libneat.a build/lib.o build/genome.o $(LDFLAGS)

build/lib.o: src/lib.cpp src/lib.h
	g++ -c src/lib.cpp -o build/lib.o $(CFLAGS)

build/genome.o: src/genome.cpp src/genome.h
	g++ -c src/genome.cpp -o build/genome.o $(CFLAGS)