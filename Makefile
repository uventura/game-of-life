all: gol

gol: gol.o includes/screen.o includes/cell.o
	gcc -o gol gol.o includes/screen.o includes/cell.o

gol.o : gol.c
	gcc -o gol.o -c gol.c

includes/screen.o : includes/screen.c
	gcc -o includes/screen.o -c includes/screen.c

includes/cell.o : includes/cell.c
	gcc -o includes/cell.o -c includes/cell.c

clean:
	rm -rf gol.o includes/screen.o includes/cell.o

mrproper:
	rm *.o