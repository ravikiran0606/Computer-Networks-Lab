#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#define MAXSIZE 100

int main(){
	int sockid,sockid2,bytes;
	int flag=0;
	char buf[MAXSIZE],buf2[MAXSIZE];
	struct sockaddr_in server,client;
	int len=sizeof(struct sockaddr);

	sockid = socket(AF_INET,SOCK_STREAM,0);

	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(3019);
	server.sin_family=AF_INET;
	
	printf("Sock id = %d\n",sockid);
	
	int bno = bind(sockid, (struct sockaddr*) &server, sizeof(struct sockaddr) );
	printf("Bind return val = %d\n",bno);
	
	int lno = listen(sockid,5);
	printf("Listen return val = %d\n",lno);

	sockid2=accept(sockid,(struct sockaddr*) &client,&len);
	printf("Got Connection from Client sock id = %d\n",sockid2);
	printf("Chat Program started :) Type bye to exit\n");
	
	while(1){
		printf("Enter text. ");		
		scanf("%s",buf);
	
		if(send(sockid2,buf,sizeof(buf),0) == -1){
			printf("Sending Error\n");
			return 0;
		}
		
		if( (bytes=recv(sockid2,buf2,sizeof(buf2),0)) == -1){
			printf("Receiving Error\n");
			return 0;
		}

		buf2[bytes]='\0';
		printf("%s\n",buf2);
		if(strcmp(buf2,"bye")==0){
			break;
		}
	}
	printf("Program Terminated\n");
	close(sockid2);

	return 0;
}
