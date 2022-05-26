
output: obj/algorithms.o obj/cryptography.o obj/main.o
	gcc -Wall -ansi -Ilibs/algorithms -Ilibs/cryptography main.c obj/algorithms.o obj/cryptography.o -o output

obj/algorithms.o: libs/algorithms/algorithms.c libs/algorithms/algorithms.h
	gcc -c libs/algorithms/algorithms.c -o obj/algorithms.o

obj/cryptography.o: obj/algorithms.o libs/cryptography/cryptography.c libs/cryptography/cryptography.h
	gcc -Ilibs/algorithms -c libs/cryptography/cryptography.c obj/algorithms.o -o obj/cryptography.o

obj/main.o: main.c
	gcc -Ilibs/algorithms -Ilibs/cryptography -c main.c obj/algorithms.o obj/cryptography.o -o obj/main.o

clean:
	del obj\*.o output.exe