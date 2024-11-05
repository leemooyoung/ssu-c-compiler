CC = gcc
CFLAGS = -Wno-int-conversion -MMD

ssu_c.out: lex.yy.o y.tab.o support.o ssu_c_main.o
	$(CC) $^ -o ssu_c.out

y.tab.c y.tab.h: ssu_c.y
	yacc -d ssu_c.y

lex.yy.c: ssu_c.l y.tab.h
	lex ssu_c.l

clean:
	rm -f ssu_c.out y.tab.c y.tab.h lex.yy.c *.o *.d

-include *.d
