# HEADERS = program.h headers.h

default: prog4

# program.o: program.c $(HEADERS)
#     gcc -c program.c -o program.o

prog4: prog4.c check.o
	gcc -g prog4.c check.o -o prog4 -lm

check.o: check.c
	gcc -c check.c -o check.o -lm

clean:
	-rm -f prog4