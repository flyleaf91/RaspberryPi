#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
        int sockfd, t, len;
        struct sockaddr_un remote;
        char str[100];

        if((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
                perror("Socket");
                exit(1);
        }

        printf("Trying to connect..., pid: %d\n", (int)getpid());

        remote.sun_family = AF_UNIX;
        strcpy(remote.sun_path, "./my_echo_socket");
        len = strlen(remote.sun_path) + sizeof(remote.sun_family);

        if(connect(sockfd, (struct sockaddr *)&remote, len) == -1) {
                perror("Connect");
                exit(1);
        }

        printf("Connected\n");

        while(printf("> "), fgets(str, 100, stdin), !feof(stdin)) {
                if(send(sockfd, str, strlen(str), 0) == -1) {
                        perror("Send");
                        exit(1);
                }

                if((t = recv(sockfd, str, 100, 0)) > 0) {
                        str[t] = '\0';
                        printf("echo> %s", str);
                } else {
                        if(t < 0) 
				perror("recv");
                        else 
				printf("Server closed connection");

                        exit(1);
                }
        }

        close(sockfd);
        return 0;
}
