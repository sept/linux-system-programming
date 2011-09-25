#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<strings.h>

#define SERV_PORT 8000
#define MXT 1024

int main(int argc, const char *argv[])
{
	struct sockaddr_in ser_addr,cli_addr;
	socklen_t cli_addr_len;
	int listefd,connfd;
	char buf[MXT];
	char str[MXT];
	int n, i = 4;

	listefd = Socket(AF_INET,SOCK_STREAM,0);
	bzero(&ser_addr,sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ser_addr.sin_port = htons(SERV_PORT);

	Bind(listefd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));
	listen(listefd,20);

	cli_addr_len = sizeof(cli_addr);
	connfd = Accept(listefd,(struct sockaddr *)&cli_addr,&cli_addr_len);

	while(i--)
	{
		n = Read(connfd,buf,sizeof(buf));
		Write(STDOUT_FILENO,buf,n);
		fgets(str, sizeof(str), stdin);
		Write(connfd, str, strlen(str));
	}
	Close(connfd);
	Close(listefd);

	return 0;
}
