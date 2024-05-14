LDLIBS += -lm
NCURSES += -lncurses
RAYLIB += -lraylib
WARNS := -Wall

dft: example_gui.c dft.o
	gcc example_gui.c dft.o $(WARNS) $(LDLIBS) $(NCURSES) $(RAYLIB) -o dft

main: main.o dft.o
	gcc main.o dft.o $(WARNS) $(LDLIBS) -o main

main.o: main.c dft.o 
	gcc -c $(WARNS) main.c

dft.o: dft.c
	gcc -c $(WARNS) dft.c

clean: 
	rm -f *.o
