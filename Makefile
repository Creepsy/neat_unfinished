CLFAGS=-g -Wall
LDFLAGS=

build/test: build/test.o build/libneat.a
	g++ build/test.o -o build/test -Lbuild -lneat $(LDFLAGS)

build/test.o: src/test.cpp
	g++ -c src/test.cpp -o build/test.o $(CFLAGS) 

build/libneat.a: build/lib.o
	ar crf build/libneat.a build/lib.o $(LDFLAGS)

build/lib.o: src/lib.cpp
	g++ -c src/lib.cpp -o build/lib.o $(CFLAGS)