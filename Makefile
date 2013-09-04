all:RefBase.o test.o
	g++ RefBase.o test.o -o all

RefBase.o:RefBase.cpp RefBase.h
	g++ -g -c RefBase.cpp -o RefBase.o

test.o:test.cpp
	g++ -g -c -fpermissive test.cpp -o test.o

clean:
	rm -rf RefBase.o test.o all
