#include<stdio.h>
#include<strings.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define SERV_PORT 8000
#define MAX 1024
#define ping_ip 192.168.1.30

int main(int argc, const char *argv[])
{
	char buf[MAX];
	char str[MAX];
	struct sockaddr_in ser_addr;
	int sockfd, n, i = 4;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	bzero(&ser_addr,sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	inet_pton(AF_INET,"ping_ip",&ser_addr.sin_addr);
	ser_addr.sin_port = htons(SERV_PORT);

	Connect(sockfd,(struct sockaddr *)&ser_addr, sizeof(ser_addr));
	while (i--)
	{
		fgets(buf, sizeof(buf), stdin);
		Write(sockfd,buf,strlen(buf));
		n = Read(sockfd, str, sizeof(str));
		Write(STDOUT_FILENO, str, n);
		bzero(str, sizeof(str));
	}
	Close(sockfd);

	return 0;

