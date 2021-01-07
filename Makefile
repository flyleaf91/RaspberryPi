all:
	gcc main.c -o backtrace -rdynamic -funwind-tables

clean:
	rm backtrace
