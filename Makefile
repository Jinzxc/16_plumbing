all: reader.o processor.o
	gcc -o reader reader.o
	gcc -o processor processor.o

reader.o: reader.c
	gcc -c reader.c

processor.o: processor.c
	gcc -c processor.c

clean:
	rm *.o