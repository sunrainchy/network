#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <linux/in.h>
#include <signal.h>
#define maxn 5
char buf[maxn];
int main(){
	int listen_fd,conn_fd;
	socklen_t len;
	struct sockaddr_in ser_addr,info;
	listen_fd=socket(AF_INET,SOCK_STREAM,0);
	if(listen_fd < 0){
		printf("Error in listen\n");
		return 0;
	}
	bzero(&ser_addr,sizeof(ser_addr));
	ser_addr.sin_family=AF_INET;
	ser_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	ser_addr.sin_port=htons(10222);
	if(bind(listen_fd,(struct sockaddr*)&ser_addr,sizeof(ser_addr))<0)
		printf("bind error\n");
	else 
		printf("bind success\n");
	listen(listen_fd,1024);
	while(1){
		int n;
		len=sizeof(info);
		conn_fd=accept(listen_fd,(struct sock_addr*)&info,&len);
		printf("%s\n",inet_ntoa(info.sin_addr));
		if(conn_fd>0){
			printf("connect success\n");
		}else{
			printf("connect failed\n");
		}
		while((n=read(conn_fd,buf,maxn))>0){
			printf("re:%s\n",buf);
		}
		printf("N:%d\n",n);
		close(conn_fd);
	}
	return 0;
}