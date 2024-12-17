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

INTERP_DEPS = \
	lex.interp.o\
	interp.tab.o\
	interp.o\
	interp.lib.o\

interp: $(INTERP_DEPS)
	$(CC) $^ -o interp

interp.tab.c interp.tab.h: interp.y
	yacc -d -b interp interp.y

lex.interp.c: interp.l interp.tab.h
	lex -o lex.interp.c interp.l

clean:
	rm -f ssu_c *.tab.c *.tab.h lex.*.c *.o *.d

# cancel implicit rule for yacc and lex

%.c: %.y

%.c: %.l

-include *.d
