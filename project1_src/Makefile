## Makefile for Project-1A -- Dan Bardin || drbardin
#
all: crop bw colorshift overlay compare

clean:
	rm -f *.o crop bw colorshift overlay compare

# src files ONLY
tarball:
	tar -czf drbardin.tar.gzip *.c *.h README Makefile 

crop: crop.o readwriteimage.o 
	gcc -ansi -pedantic -g -o crop crop.o readwriteimage.o

bw: bw.o readwriteimage.o 
	gcc -ansi -pedantic -g -o bw bw.o readwriteimage.o

colorshift: shift.o readwriteimage.o
	gcc -ansi -pedantic -g -o colorshift shift.o readwriteimage.o

overlay: overlay.o readwriteimage.o
	gcc -ansi -pedantic -g -o overlay overlay.o readwriteimage.o

compare: compare.o readwriteimage.o
	gcc -ansi -pedantic -g -o compare compare.o readwriteimage.o

crop.o: crop.c readwriteimage.h
	gcc -ansi -pedantic -c -g crop.c

bw.o: bw.c readwriteimage.h
	gcc -ansi -pedantic -c -g bw.c

shift.o: shift.c readwriteimage.h
	gcc -ansi -pedantic -c -g shift.c

overlay.o: overlay.c readwriteimage.h
	gcc -ansi -pedantic -c -g overlay.c
	
readwriteimage.o: readwriteimage.c readwriteimage.h
	gcc -ansi -pedantic -c -g readwriteimage.c

compare.o: compare.c readwriteimage.h
	gcc -ansi -pedantic -c -g compare.c
