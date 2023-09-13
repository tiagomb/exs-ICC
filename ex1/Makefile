CFLAGS = -Wall -g
LIBS = -lm

all: main

main: main.o interval.o
	gcc -o main main.o interval.o $(LIBS)

main.o: main.c
	gcc -c main.c $(CFLAGS) $(LIBS)

interval.o: interval.c interval.h
	gcc -c interval.c $(CFLAGS) $(LIBS)

removeObjects:
	-rm *.o

clean:
	-rm *.o main