XENO ?= /usr/xenomai

CC=g++
INCLUDE= -I/usr/xenomai/include
OPTIONS= -D_GNU_SOURCE -D_REENTRANT -D__XENO__
SRC=latency.c
LIBS= -Xlinker -rpath -Xlinker /usr/xenomai/lib -lnative -L/usr/xenomai/lib -lxenomai -lpthread -lrt


all:
	$(CC) $(INCLUDE) $(OPTIONS) $(SRC) $(LIBS) 