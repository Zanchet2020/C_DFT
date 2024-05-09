LDLIBS += -lm
NCURSES += -lncurses
WARNS := -Wall

example_gui: example_gui.c dft.o
	gcc example_gui.c dft.o $(WARNS) $(LDLIBS) $(NCURSES) -o example_gui

main: main.o dft.o
	gcc main.o dft.o $(WARNS) $(LDLIBS) -o main

main.o: main.c dft.o 
	gcc -c $(WARNS) main.c

dft.o: dft.c
	gcc -c $(WARNS) dft.c

clean: 
	rm -f *.o
