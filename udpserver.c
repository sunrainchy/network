#include <sys/socket.h>
#include <unistd.h>
#include <linux/in.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#define SERVER_PORT 10222
#define maxn 1024
char str[maxn];
int main(){
	struct sockaddr_in server,client;
	int udp_sock_fd,len;
	bzero(&server,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_port=htons(SERVER_PORT);
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	udp_sock_fd=socket(AF_INET,SOCK_DGRAM,0);
	if(udp_sock_fd < 0){
		printf("Create socket error \n");
		return 0;
	}
	bind(udp_sock_fd,(struct sockaddr*)&server,sizeof(server));
	while(1){
		len=recvfrom(udp_sock_fd,str,sizeof(str),0,(struct sock_addr*)&client,sizeof(client));
		printf("RECV:%s\n",str);
		sendto(udp_sock_fd,str,len,0,(struct sock_addr*)&client,sizeof(client));
	}
	return 0;
}
