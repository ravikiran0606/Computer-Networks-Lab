#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#define MAXSIZE 100

struct msg{
	char text[MAXSIZE];
	int no;
};

int main(){
	int sockid,sockid2,bytes,bytes2;
	struct msg m;
	int flag=0;
	char buf[MAXSIZE];
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
	
	if( ( bytes = recv(sockid2,&m,sizeof(m),0) ) == -1){
		printf("Error Receiving.");
		return 0;
	}
	
	printf("The Contents received are : %s and %d\n",m.text,m.no);	
		
	close(sockid2);

	return 0;
}
