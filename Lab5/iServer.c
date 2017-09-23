#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<signal.h>
#include<stdlib.h>
#include<netinet/in.h>
#define PORT 3019
#define MAXSIZE 100

int main()
{
	int sockfd,newSockfd,n,clientAddressLength,pid;
	struct sockaddr_in serverAddress,clientAddress;
	char msg[MAXSIZE],msg2[MAXSIZE];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	memset(&serverAddress,0,sizeof(serverAddress));
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_addr.s_addr=htons(INADDR_ANY);
	serverAddress.sin_port=htons(PORT);
	bind(sockfd,(struct sockaddr *)&serverAddress,sizeof(serverAddress));
	listen(sockfd,5);
	
	while(1){
		printf("Server waiting for a new Connection.\n");
		clientAddressLength=sizeof(clientAddress);
		newSockfd=accept(sockfd,(struct sockaddr*)&clientAddress,&clientAddressLength);
		printf("Connected to client : %s\n",inet_ntoa(clientAddress.sin_addr));
		
		while(1){
			n=recv(newSockfd,msg,MAXSIZE,0);
			msg[n]='\0';
			printf("Received : %s from Client id : %d\n",msg,newSockfd);
			if(strcmp(msg,"bye")==0){
				close(newSockfd);
				break;
			}
			printf("For Client id : %d, Enter the message : ",newSockfd);
			scanf("%s",msg2);
			send(newSockfd,msg2,sizeof(msg2),0);
		}
	}
	return 0;
}
