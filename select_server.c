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
char buf[maxn];
int fd_rec[maxn];
int num;
int main(){
	int connfd,listenfd,len,max_fd=-1;
	int i,j,k,n;
	fd_set conn_set;
	struct sockaddr_in server_addr,info;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(SERVER_PORT);
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	bind(listenfd,(struct sock_addr *)&server_addr,sizeof(server_addr));
	listen(listenfd,QUEUE_NUM);
	for(i=0;i<maxn;i++)
		fd_rec[i]=-1;
	FD_ZERO(&conn_set);
	FD_SET(listenfd,&conn_set);
	fd_rec[listenfd]=1;
	max_fd=max_fd > listenfd ? max_fd : listenfd;
	num=1;
	while(1){
		len=sizeof(info);
		//connfd=accept(listenfd,(struct sockaddr*)&info,&len);
		FD_ZERO(&conn_set);
		for(i=0;i<maxn;i++){
			if(fd_rec[i]==1){
				printf("H:%d ",i);
				FD_SET(i,&conn_set);
			}
		}
		printf("before\n");
		select(max_fd+1,&conn_set,0,0,NULL);
		printf("after\n");
		if(FD_ISSET(listenfd,&conn_set)){
			connfd=accept(listenfd,(struct scokaddr*)&info,&len);
			if(connfd<0){
				if(errno==EINTR){
					printf("Accept abrupt\n");
					continue;
				}else{
					printf("Accept Error\n");
				}
			}else{
				max_fd=max_fd > connfd ? max_fd : connfd;
				fd_rec[connfd]=1;
				printf("%d\n",connfd);
				continue;
			}
		}
		for(i=0;i<maxn;i++){
			if(fd_rec[i]==1){
				if(FD_ISSET(i,&conn_set)){
					n=read(i,buf,sizeof(buf));
					if(n<=0){
						close(i);
						fd_rec[i]=-1;
						printf("close socked %d\n",i);
					}else{
						printf("READ:%s\n",buf);
						write(i,buf,strlen(buf));
					}
				}
			}
		}
		printf("Run success \n");
	}
	return 0;
}
