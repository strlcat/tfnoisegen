PROGS = tfrand
PROGSRCS = $(PROGS:=.c)
PROGOBJS = $(PROGSRCS:.c=.o)
SRCS = $(filter-out $(PROGSRCS), $(wildcard *.c))
HDRS = $(wildcard *.h)
OBJS = $(SRCS:.c=.o)

ifneq (,$(DEBUG))
override CFLAGS+=-Wall -O0 -g
else
override CFLAGS+=-O3
endif

default: $(OBJS) libtf.a tfrand
all: $(OBJS) libtf.a $(PROGS)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c -o $@ $<

libtf.a: $(OBJS)
	$(AR) cru $@ $^

$(PROGS): %: %.o libtf.a
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f libtf.a $(OBJS) $(PROGOBJS) $(SUPPOBJS) $(PROGS)
