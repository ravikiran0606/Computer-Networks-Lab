#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<stdlib.h>
#define MAXSIZE 100

struct msg{
	char text[MAXSIZE];
	int no;
};

int main(int argc,char* argv[]){
	int csockid;
	char buf[MAXSIZE];
	struct sockaddr_in caddr;
	struct msg m;
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
	
	printf("Enter the text. ");
	scanf("%s",m.text);
	printf("Enter the number. ");
	scanf("%d",&m.no);
	
	if( send(csockid,&m,sizeof(m),0) == -1){
		printf("Error Sending.");
		return 0;
	}	

	close(csockid);
	
	return 0;
}

