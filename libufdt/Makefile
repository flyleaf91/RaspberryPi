all:
	make -C libfdt
	make -C libufdt_sysdeps
	gcc -I./libfdt dt_table.c -Ilibufdt_sysdeps/include  mkdtimg.c  mkdtimg_cfg_create.c  mkdtimg_core.c  mkdtimg_create.c  mkdtimg_dump.c -o mkdtimg -L ./ -lfdt -lufdt_sysdeps

clean:
	rm mkdtimg
	make -C libfdt clean
	make -C libufdt_sysdeps clean
	rm *.so
