#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#define MAXSIZE 100

int main(){
	int sockid,sockid2,bytes,bytes2;
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
		
	if( (bytes=recv(sockid2,buf,MAXSIZE-1,0)) == -1){
		printf("Receiving Error\n");
		return 0;
	}
	buf[bytes]='\0';
	//printf("File Name is : %s\n",buf);
	
	int fd = open(buf,O_RDWR);
	bytes2=read(fd,buf2,MAXSIZE);
	buf2[bytes2]='\0';
	close(fd);

	//printf("Contents : %s\n",buf2);

	if( send(sockid2,buf2,sizeof(buf2),0) == -1){
		printf("Error Sending\n");
	}	

	close(sockid2);

	return 0;
}
