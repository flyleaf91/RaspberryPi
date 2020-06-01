# Makefile
#
# This is not a complete Makefile of itself.  Instead, it is designed to
# be easily embeddable into other systems of Makefiles.
#

OBJS = libufdt_sysdeps_posix.o
LIB = libufdt_sysdeps.a

all: $(LIB)
	mv $(LIB) ../

%.o : %.c
	$(info $<)
	$(info $@)
	gcc -Iinclude -c $< -o $@

$(LIB) : $(OBJS)
	rm -f $@
	ar cr $@ $(OBJS)
	rm -f $(OBJS)

clean: 
	rm $(LIB)
