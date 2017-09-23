#include<stdio.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#define PORT 3019
#define SERVER_IP "127.0.0.1"
#define MAXSIZE 100

int main()
{
	int sockfd,n;
	struct sockaddr_in serverAddress;
	char msg1[MAXSIZE],msg2[MAXSIZE];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	memset(&serverAddress,0,sizeof(serverAddress));
	printf("Socket id : %d\n",sockfd);	

	serverAddress.sin_family=AF_INET;
	serverAddress.sin_addr.s_addr=inet_addr(SERVER_IP);
	serverAddress.sin_port=htons(PORT);
	connect(sockfd,(struct sockaddr *)&serverAddress,sizeof(serverAddress));

	while(1){
 		printf("Enter message : ");
		scanf("%s",msg1);
		send(sockfd,msg1,sizeof(msg1),0);
		if(strcmp(msg1,"bye")==0){
			break;
		}
		n=recv(sockfd,msg2,MAXSIZE,0);
		printf("Received message : %s\n",msg2);
	}
	
	close(sockfd);
	return 0;
}
