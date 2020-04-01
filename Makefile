all:
	gcc -rdynamic -funwind-tables main.c backtrace.c -o backtrace

clean:
	rm backtrace
