obj = server.o client.o

all: $(obj)
	gcc -o server server.o
	gcc -o client client.o

*.o : *.c
	gcc -c *.c

.PNONY : clean
clean :
	rm *.o
	rm server
	rm client
	rm my_echo_socket

