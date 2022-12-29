#***********************************************
#
#	Simple Makefile for Makemask
#
#
#**********************************************

#Support for sgi systems
IRIX ?=  0

#Build the irix binary using qemu-irix with an "irix root"
CROSS ?= 0

#IRIX 6.5.30 root
ROOT = tools/irix


#maybe -KPIC should be necesary
ifeq ($(IRIX),1)
 CFLAGS :=  -I /usr/include/ -g0 -O1 -KPIC -mips1 -fullwarn -wlint,-fph -Wab,-r4300_mul -Xcpluscomm -nostdinc
endif

ifeq ($(CROSS),1)
 CFLAGS := -g0 -O1 -KPIC -mips1 -fullwarn -wlint,-fph -Wab, -Xcpluscomm -nostdinc -I $(ROOT)/usr/include
 CC := /usr/bin/qemu-irix -silent -L $(ROOT) $(ROOT)/usr/bin/cc
else

 CFLAGS :=  -Wall -O1 -g0 -fPIC
endif

all:
	$(CC) $(CFLAGS) makemask.c -o makemask


clean:
	rm makemask
