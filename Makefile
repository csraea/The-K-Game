cc = gcc
CFLAGS = -std=c11 -Werror -Wall
LDLIBS = -lm -lcurses
OUTPUT = game

all : main
main : main.o k.o hof.o ui.o
	$(cc) main.o hof.o k.o ui.o -o game $(CFLAGS) $(LDLIBS)
main.o : main.c
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 main.c
	$(cc) -c main.c $(CFLAGS) $(LDLIBS)
k.o : k.c
	cppcheck --enable=performance --error-exitcode=1 k.c
	$(cc) -c k.c $(CFLAGS) $(LDLIBS)
hof.o : hof.c
	cppcheck --enable=performance --error-exitcode=1 hof.c
	$(cc) -c hof.c $(CFLAGS) $(LDLIBS)
ui.o :  ui.c
	cppcheck --enable=performance --error-exitcode=1 ui.c
	$(cc) -c ui.c $(CFLAGS) $(LDLIBS)
clean:
	rm *o
	rm $(OUTPUT)
