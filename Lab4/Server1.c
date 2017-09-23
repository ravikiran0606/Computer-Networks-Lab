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
	char method[MAXSIZE];
	char version[MAXSIZE];
	char url[MAXSIZE];
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

	if(strcmp(m.method,"GET") == 0 ){
		int fd = open(m.url,O_RDWR);
		bytes2 = read(fd,buf,sizeof(buf));
		buf[bytes2]='\0';
		close(fd);
		
		if( send(sockid2,buf,sizeof(buf),0) == -1){
			printf("Error Sending.");
			return 0;
		}
		printf("Contents Sent.\n");	
	}
	else if(strcmp(m.method,"POST") == 0){
		int fd = open(m.url,O_RDWR);
                bytes2 = read(fd,buf,sizeof(buf));
                buf[bytes2]='\0';
                close(fd);
		
		printf("Contents Posted.\n");
		printf("The Contents of the file are : %s\n",buf);
	}	

		
	close(sockid2);

	return 0;
}
