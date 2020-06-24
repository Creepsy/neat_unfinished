CFLAGS=-g -Wall
LDFLAGS=

build/test: build/test.o build/libneat.a
	g++ build/test.o -o build/test -Lbuild -lneat $(LDFLAGS)

build/test.o: src/test.cpp src/util.h src/genome.h
	g++ -c src/test.cpp -o build/test.o $(CFLAGS) 

build/libneat.a: build/lib.o build/genome.o build/innovations.o
	ar crf build/libneat.a build/lib.o build/genome.o build/innovations.o $(LDFLAGS)

build/lib.o: src/lib.cpp src/lib.h
	g++ -c src/lib.cpp -o build/lib.o $(CFLAGS)

build/genome.o: src/genome.cpp src/genome.h
	g++ -c src/genome.cpp -o build/genome.o $(CFLAGS)

build/innovations.o: src/innovations.cpp src/innovations.h
	g++ -c src/innovations.cpp -o build/innovations.o $(CFLAGS)