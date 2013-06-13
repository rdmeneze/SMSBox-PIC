.SUFFIXES: .cpp.o .cpp

include ../../Makefile.in

LIBS	= -L../ -liniFile -lm
INCLUDE	= -I../

OBJS = 	ini_test.o

all: ini_test memleak_test

ini_test: ${OBJS} Makefile
	${CPP} ${DEBUG} ${OBJS} -o $@ ${LIBS}

memleak_test: memleak_test.o Makefile
	${CPP} ${DEBUG} memleak_test.o -o $@ ${LIBS}

ini_test.o: ../libiniFile.a
memleak_test.o: ../libiniFile.a

clean:
	rm -f *.o *~ *.a *.sav

.cpp.o:	
	${CPP} ${CFLAGS} ${INCLUDE} ${DEFINES} -c $*.cpp
