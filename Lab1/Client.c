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
	char buf[MAXSIZE];
	struct sockaddr_in caddr;
	struct hostent *he;	
	int bytes;

	csockid= socket(AF_INET,SOCK_STREAM,0);
	printf("Client Sock id = %d\n",csockid);

	/*if((he = gethostbyname(argv[1]))==NULL){
		printf("Get host by Name Error");
		return 0;
	}*/

	if(csockid < 0){
		printf("Socket Error");
		return 0;
	}

	caddr.sin_port=htons(3019);
	caddr.sin_family=AF_INET;
	caddr.sin_addr.s_addr=inet_addr("127.0.0.1");

	//caddr.sin_addr = *( (struct in_addr*)he->h_addr );
	//memset(&(caddr.sin_zero),0,8);
		

	if( connect(csockid,(struct sockaddr*) &caddr,sizeof(struct sockaddr) )==-1){
		printf("Error Connecting");
		return 0;
	}	

	if( (bytes=recv(csockid,buf,MAXSIZE-1,0)) == -1){
		printf("Error Receiving");
		return 0;
	} 

	buf[bytes] = '\0';
	printf("Content received is %s\n",buf);
	close(csockid);
	
	return 0;
}

