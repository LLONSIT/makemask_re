#***********************************************
#
#	Simple Makefile for Makemask
#
#
#**********************************************

#Support for sgi systems
IRIX ?=  0

#Build the irix binary using qemu-irix with an "irix root"
CROSS ?= 1

#IRIX 6.5.30 root
ROOT = tools/irix


#maybe -KPIC should be necesary
SGI_CFLAGS :=  -I /usr/include/ -g0 -O1 -KPIC -mips1 -fullwarn -wlint,-fph -Wab,-r4300_mul -Xcpluscomm -nostdinc

ifeq ($(CROSS),1)
 CFLAGS := -g0 -O1 -KPIC -mips1 -fullwarn -wlint,-fph -Wab, -Xcpluscomm -nostdinc -I $(ROOT)/usr/include
 CC := /usr/bin/qemu-irix -silent -L $(ROOT) $(ROOT)/usr/bin/cc
else

 CFLAGS :=  -Wall -O1 -g0 -fPIC
endif

all:

ifeq ($(IRIX),1)
	$(CC) $(SGI_CFLAGS) makemask.c -o makemask
else
	$(CC) $(CFLAGS) makemask.c -o makemask
endif

clean:
	rm makemask
