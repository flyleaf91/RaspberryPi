#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <error.h> 
#include <errno.h> 
#include <sys/socket.h> 
#include <stdlib.h> 

const char* str = "SOCKET PAIR TEST.";

int main(int argc, char* argv[]){
    char buf[128] = {0};
    int socket_pair[2]; 
    pid_t pid; 

    if(socketpair(AF_UNIX, SOCK_STREAM, 0, socket_pair) == -1 ) { 
        printf("Error, socketpair create failed, errno(%d): %s\n", errno, strerror(errno));
        return EXIT_FAILURE; 
    } 

    pid = fork();
    if(pid < 0) {
        printf("Error, fork failed, errno(%d): %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    } else if(pid > 0) {
        //关闭另外一个套接字
        close(socket_pair[1]);
        int size = write(socket_pair[0], str, strlen(str));
        printf("Write success, pid: %d\n", getpid());

    } else if(pid == 0) {
        //关闭另外一个套接字
        close(socket_pair[0]);
        read(socket_pair[1], buf, sizeof(buf));        
        printf("Read result: %s, pid: %d\n",buf, getpid());
    }

    for(;;) {
        sleep(1);
    }

    return EXIT_SUCCESS;    
} 
