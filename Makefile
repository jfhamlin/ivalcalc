DBG_CFLAGS = -g -DDEBUG
CFLAGS = -Wall -std=c++11 -stdlib=libc++
OPTFLAGS = -O3

CC=clang++

HDRS =
SRCS = src/constraint_network.cpp src/constraint_types.cpp

.PHONY: clean test

all: foo

debug: CFLAGS += ${DBG_CFLAGS}
debug: OPTFLAGS =
debug: all

foo: ${SRCS} ${HDRS}
	${CC} ${CFLAGS} ${OPTFLAGS} -o $@ ${SRCS}

clean:
	-rm *.o *~ foo
