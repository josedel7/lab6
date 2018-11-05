CC=gcc
CFLAGS=-lWarn -pedantic
LW=-lwiringPi
CFLAG=-Wall -pedantic

irtester: irtester.o libmyifttt.a
	$(CC) irtester.o -L. -lmyifttt -lcurl -o irtester $(LW)
 
libmyifttt.a:	ifttt.o
	ar -rcs libmyifttt.a ifttt.o

ifttt.o:	ifttt.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<

irtester.o:	irtester.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<

clean:
	rm irtester *.o

