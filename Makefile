CC = gcc
CFLAGS = -Wno-int-conversion -MMD -g

DEPS = \
	lex.yy.o\
	y.tab.o\
	support.o\
	semantic.o\
	print.o\
	print_sem.o\
	ssu_c_main.o\

ssu_c: $(DEPS)
	$(CC) $^ -o ssu_c

y.tab.c y.tab.h: ssu_c.y
	yacc -d ssu_c.y

lex.yy.c: ssu_c.l y.tab.h
	lex ssu_c.l

clean:
	rm -f ssu_c y.tab.c y.tab.h lex.yy.c *.o *.d

-include *.d
