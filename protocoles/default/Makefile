SHELL = /bin/sh

TARGET = display

SRCS = main.cc

### Default Xenomai installation path
XENO ?= /usr/xenomai

XENOCONFIG=$(shell PATH=$(XENO):$(XENO)/bin:$(PATH) which xeno-config 2>/dev/null)

CC=$(shell $(XENOCONFIG) --cc) -ldl

CFLAGS=$(shell $(XENOCONFIG) --xeno-cflags) $(MY_CFLAGS) -lnative -lanalogy -lrtdm

LDFLAGS=$(shell $(XENOCONFIG) --xeno-ldflags) $(MY_LDFLAGS)

# This includes the library path of given Xenomai into the binary to make live
# easier for beginners if Xenomai's libs are not in any default search path.
LDFLAGS+=-Xlinker -rpath -Xlinker $(shell $(XENOCONFIG) --libdir)  \
	-lm -lX11 -g -ggdb
REXENO_PATH=/usr/local/lib

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) core *~

$(TARGET) : $(OBJS)
	g++ $(SRCS) -o $(TARGET) /usr/lib/libsession.a /usr/lib/librecorder.a /usr/lib/libdriver.a /usr/lib/libconfiguration.a -lGL -lboost_program_options -lglut $(CFLAGS) $(LDFLAGS)

noxeno:
	g++ $(SRCS) -o $(TARGET) -Wl,-rpath /usr/local/lib -Wl,-rpath /usr/local/lib/libsession.so -lsession -lrecorder -ldriver -lconfiguration
