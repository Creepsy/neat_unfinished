<<<<<<< HEAD
CLFAGS=-g -Wall
=======
CLFAGS=-g 
>>>>>>> 1271133ce8d1afb5f44ecd4efe469ec6e932aaaf
LDFLAGS=

build/test: build/test.o build/libneat.so
	g++ build/test.o -o build/test -Lbuild -lneat $(LDFLAGS)

build/test.o: src/test.cpp
	g++ -c src/test.cpp -o build/test.o $(CFLAGS) 

build/libneat.so: build/lib.o
	g++ -shared build/lib.o -o build/libneat.so $(LDFLAGS)

build/lib.o: src/lib.cpp
	g++ -c src/lib.cpp -o build/lib.o $(CFLAGS)