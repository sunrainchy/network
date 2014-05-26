#include <sys/socket.h>
#include <unistd.h>
#include <linux/in.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
char buf[10000];
int main(){
	int connfd,sock_fd;
	struct sockaddr_in client,info;
	socklen_t len;
	sock_fd=socket(AF_INET,SOCK_STREAM,0);
	bzero(&client,sizeof(client));
	client.sin_family=AF_INET;
	client.sin_port=htons(10222);
	client.sin_addr.s_addr=inet_addr("192.168.0.15");
	if(connect(sock_fd,(struct sockaddr*)&client,sizeof(client))<0)printf("connect error\n");
	else printf("success\n");
	return 0;
}

