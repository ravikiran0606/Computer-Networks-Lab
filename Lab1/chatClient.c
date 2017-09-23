#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<stdlib.h>
#define MAXSIZE 100

int main(int argc,char* argv[]){
	int csockid;
	char buf[MAXSIZE],buf2[MAXSIZE];
	struct sockaddr_in caddr;
	int bytes;

	csockid= socket(AF_INET,SOCK_STREAM,0);
	printf("Client Sock id = %d\n",csockid);

	if(csockid < 0){
		printf("Socket Error");
		return 0;
	}

	caddr.sin_port=htons(3019);
	caddr.sin_family=AF_INET;
	caddr.sin_addr.s_addr=inet_addr("127.0.0.1");

	if( connect(csockid,(struct sockaddr*) &caddr,sizeof(struct sockaddr) )==-1){
		printf("Error Connecting");
		return 0;
	}	 

	int flag=0;
	
	while(1){
		
		if( (bytes=recv(csockid,buf,sizeof(buf),0)) == -1){
			printf("Error Receiving\n");
			return 0;
		}
		
		buf[bytes]='\0';
		
		printf("%s\n",buf);
		printf("Enter text ");
		scanf("%s",buf2);
		
		if( send(csockid,buf2,sizeof(buf2),0) == -1){
			printf("Error Sending\n");
			return 0;
		}
		if(strcmp(buf2,"bye")==0){
			break;
		}
	}

	close(csockid);
	
	return 0;
}

