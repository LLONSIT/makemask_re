#***********************************************
#
#	Simple Makefile for Makemask
#
#
#******++++++++++++++++++++++++++++++++++++++++++


all: 
	@gcc makemask.c -o makemask
	@printf "Done!\n"

clean:
	rm makemask
