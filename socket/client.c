#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>

#define AERV_PORT 8000
int main(int argc, char *argv[])
{
    int sockfd, n;
    char buf[80];
    char *str;
    struct sockaddr_in servaddr;

    if (argc != 2) 
    {
        fputs("usage : ./client message \n", stderr); 
        exit(1);
    }
    str = argv[1];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    servaddr.sin_port = htons(AERV_PORT);

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    write(sockfd, str, strlen(str));

    n = read(sockfd, buf, sizeof(buf));
    printf("Response from server : \n");
    write(STDOUT_FILENO, buf, n);

    close(sockfd);

    return 0;
}

