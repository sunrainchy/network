#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <linux/in.h>
#include <signal.h>
#define maxn 1024
#define QUEUE_NUM 128
#define SERVER_PORT 10222
int main(){
	int connfd,listenfd,len;
	struct sockaddr_in server_addr,info;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(SERVER_PORT);
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	bind(listenfd,(struct sock_addr *)&server_addr,sizeof(server_addr));
	listen(listenfd,QUEUE_NUM);
	while(1){
		len=sizeof(info);
		connfd=accept(listenfd,(struct sockaddr*)&info,&len);
		if(connfd < 0){
			if(errno==EINTR)
				continue;
			printf("Accept Error\n");
		}
		printf("success \n");
		close(connfd);
	}
	return 0;
}
