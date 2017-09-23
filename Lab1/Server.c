#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>

int main(){
	int sockid,sockid2;
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

	do{
		sockid2=accept(sockid,(struct sockaddr*) &client,&len);
		printf("Got Connection from Client sock id = %d\n",sockid2);
		//printf("Got Connection from Address = %s\n",inet_ntoa(client.sin_addr));
		if( send(sockid2,"Hi, This is Ravi Kiran!\n",24,0) == -1){
			printf("Error Sending\n");
			return 0;
		}		
		close(sockid2);

	}while(len==-1);

	return 0;
}
