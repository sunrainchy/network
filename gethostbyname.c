#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#define maxn 1024
char str[maxn];
int main(int argc,char **argv){
	struct hostent *ptr;
	if(argc!=2){
		printf("Usage: %s [name]\n",argv[0]);
		return 0;
	}
	if((ptr=gethostbyname(argv[1]))==NULL){
		printf("%s\n",hstrerror(h_errno));
		return 0;
	}
	char **p=ptr->h_aliases;
	while(*p){
		printf("%s\n",*p);
		p++;
	}
	p=ptr->h_addr_list;
	while(*p){
		printf("%s\n",inet_ntop(ptr->h_addrtype,*p,str,sizeof(str)));
		p++;
	}
	return 0;
}
