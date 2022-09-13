all:
	gcc -fcommon main.c Controllers/*.c
	./a.out