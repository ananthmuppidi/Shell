all:
	gcc -fcommon -g main.c Controllers/*.c -o shell
	