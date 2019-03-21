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

default: $(OBJS) libtfng.a tfrand
all: $(OBJS) libtfng.a $(PROGS)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c -o $@ $<

libtfng.a: $(OBJS)
	$(AR) cru $@ $^

$(PROGS): %: %.o libtfng.a
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f libtfng.a $(OBJS) $(PROGOBJS) $(SUPPOBJS) $(PROGS)
