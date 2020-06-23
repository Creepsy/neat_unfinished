CLFAGS=-g -O3
LDFLAGS=-O4

build/test: build/test.o build/libneat.so
	g++ build/test.o -o build/test -Lbuild -lneat $(LDFLAGS)

build/test.o: src/test.cpp
	g++ -c src/test.cpp -o build/test.o $(CFLAGS) 

build/libneat.so: build/lib.o
	g++ -shared build/lib.o -o build/libneat.so $(LDFLAGS)

build/lib.o: src/lib.cpp
	g++ -c src/lib.cpp -o build/lib.o $(CFLAGS)