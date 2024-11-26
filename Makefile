determinant.out: matrix.o main.o
	gcc -o determinant.out matrix.o main.o

matrix.o: matrix.c matrix.h
	gcc -c matrix.c

main.o: main.c matrix.h
	gcc -c main.c

clean:
	rm -f *.o determinant.out
