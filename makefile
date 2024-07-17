all: main

main: main.o cisj.o
	$(LINK.c) -o $@ -Bstatic main.o cisj.o -lm

cisj.o: cisj.c cisj.h
	$(COMPILE.c)  -g cisj.c

clean:
	$(RM) *.o main relat saida

