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
	char method[MAXSIZE];
	char version[MAXSIZE];
	char url[MAXSIZE];
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
	
	printf("Enter the method name. ");
	scanf("%s",m.method);
	printf("Enter the version. ");
	scanf("%s",m.version);
	printf("Enter the URL. ");
	scanf("%s",m.url);
	
	if( send(csockid,&m,sizeof(m),0) == -1){
		printf("Error Sending.");
		return 0;
	}	

	if(strcmp(m.method,"GET") == 0 ){
		if( ( bytes = recv(csockid,buf,MAXSIZE-1,0) ) == -1){
			printf("Error Receiving.");
			return 0;
		}		
		printf("The Contents of the file is : %s\n",buf);
	}		
	else if(strcmp(m.method,"POST") == 0 ){
		printf("File Successfully posted.\n");
	}

	close(csockid);
	
	return 0;
}

