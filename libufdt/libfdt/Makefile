# Makefile
#
# This is not a complete Makefile of itself.  Instead, it is designed to
# be easily embeddable into other systems of Makefiles.
#

OBJS = fdt.o fdt_ro.o fdt_wip.o fdt_sw.o fdt_rw.o fdt_strerror.o fdt_empty_tree.o \
	fdt_addresses.o fdt_overlay.o acpi.o
LIB = libfdt.a

all: $(LIB)
	mv $(LIB) ../

%.o : %.c
	$(info $<)
	$(info $@)
	gcc -c $< -o $@

$(LIB) : $(OBJS)
	rm -f $@
	ar cr $@ $(OBJS)
	rm -f $(OBJS)

clean: 
	rm $(LIB)
