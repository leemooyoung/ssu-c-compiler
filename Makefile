CC = gcc

ssu_c.out: lex.yy.o y.tab.o ssu_c_main.o
	$(CC) lex.yy.o y.tab.o ssu_c_main.o -o ssu_c.out

y.tab.c y.tab.h: ssu_c.y
	yacc -d ssu_c.y

lex.yy.c: ssu_c.l y.tab.h
	lex ssu_c.l

clean:
	rm -f ssu_c.out y.tab.c y.tab.h lex.yy.c *.o
