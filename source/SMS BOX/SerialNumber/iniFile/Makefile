.SUFFIXES: .cpp.o .cpp

include ../Makefile.in

OBJS = 	iniFile.o

all: libiniFile.a

libiniFile.a: ${OBJS} Makefile
	${LIBCOMMAND} $@ ${OBJS}
	${RANLIB} $@

iniFile.o: iniFile.h

clean:
	rm -f *.o *~ *.a

.cpp.o:	
	${CPP} ${CFLAGS} ${INCLUDE} ${DEFINES} -c $*.cpp
