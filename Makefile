LDLIBS += -lm

main: main.o dft.o
	gcc main.o dft.o $(LDLIBS) -o main

main.o: main.c dft.o 
	gcc -c main.c dft.o

dft.o: dft.c dft.h 
	gcc -c dft.c


clean: 
	rm -f *.o
