# Makefile

all: works.c works.h bike.c bike.h menu.c menu.h ai.h ai.c main.c
	gcc -c  works.c -o works.o
	gcc -c  bike.c -o bike.o
	gcc -c  menu.c -o menu.o
	gcc -c  ai.c -o ai.o
	gcc  main.c works.o bike.o menu.o ai.o -o project -lncurses -lpthread

clean:
	rm -rf *.o
	rm -rf project

