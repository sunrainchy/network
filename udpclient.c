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
	int udp_sock_fd,len;
	struct sockaddr_in client,server;
	bzero(&client,sizeof(client));
	client.sin_family=AF_INET;
	client.sin_port=htons(SERVER_PORT);
	client.sin_addr.s_addr=inet_addr("192.168.0.15");
	udp_sock_fd=socket(AF_INET,SOCK_DGRAM,0);
	if(udp_sock_fd < 0){
		printf("Create socket error\n");
		return 0;
	}
	strcpy(str,"hello world\n");
	int t=1024,num=0;
	connect(udp_sock_fd,(struct sockaddr*)&client,sizeof(client));
	while(t--){
		write(udp_sock_fd,str,sizeof(str));
		read(udp_sock_fd,str,sizeof(str));
	}	
	return 0;
}

