idir = ../
odir = ./output
ldir = ./libs

libs = -lm

cc = gcc
cflags = -I$(idir) -std=c1x

sources = ./test.c
sources += $(shell find ../thread/ -name '*.c')

deps = $(shell find ../thread/ -name '*.h')

obj = $(sources:.c = .o)

%.o:%.c $(deps)
	$(cc) -c -o $@ $< $(cflags)

all: $(obj)
	$(cc) -o $@ $^ $(cflags) $(libs)

.PHONY: clean

clean:
	rm -f $(odir)/*.o *~ core $(idir)/*~