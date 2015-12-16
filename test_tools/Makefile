#
# a very simple Makefile for miniLZO
#
# Copyright (C) 1996-2015 Markus F.X.J. Oberhumer
#

SOURCES = $(wildcard *.c)
TESTS=$(wildcard *.sh)



# Make sure that minilzo.h, lzoconf.h and lzodefs.h are in the
# current dircectory. Otherwise you may want to adjust CPPFLAGS.
CPPFLAGS = -I.. 

GCC_CFLAGS = -s -Wall -O2 -fomit-frame-pointer
default:$(SOURCES:%.c=%) $(TESTS:%.sh=%.test)
	@echo "Done"
%:%.c
	gcc $(CPPFLAGS) $(GCC_CFLAGS) -o $@ $(@:%=%.c) ../minilzo.c
%.test:%
	bash $(<:%=%.sh)
clean:
	rm -rf $(SOURCES:%.c=%)

