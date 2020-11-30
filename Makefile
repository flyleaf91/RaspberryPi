all:
	gcc bctest.c binder.c -o bctest
	gcc client.c binder.c -o client
	gcc service.c binder.c -o service
	gcc service_manager.c binder.c -o service_manager

clean:
	bctest client service service_manager

