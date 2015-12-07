READWRITE : ReadWrite.o
	gcc ReadWrite.o -o READWRITE -lpthread -lrt

ReadWrite.o : ReadWrite.c
	gcc -std=c99 -c ReadWrite.c
