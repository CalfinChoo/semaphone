ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: control.o write.o
	$(CC) -o control control.o
	$(CC) -o write write.o

control.o: control.c
	$(CC) -c control.c

write.o: write.c
	$(CC) -c write.c

memcheck:
	valgrind --leak-check=yes ./test

clean:
	rm *.o
	rm *~
