#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<string.h>

int main(){
	int sd,bd,ld,size,ad,len,fd;
	char content[1000];
	struct sockaddr_in server;
	struct sockaddr_in client;	
	struct sockaddr_storage serverStorage;
	server.sin_family=AF_INET;
	server.sin_port=3019;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");

	sd=socket(AF_INET,SOCK_DGRAM,0);
	bd=bind(sd,(struct sockaddr*)&server,sizeof(struct sockaddr));
	printf("Socket id : %d\n",sd);	

	char fileName[100];
	recvfrom(sd,fileName,sizeof(fileName),0,(struct sockaddr *)&serverStorage,&size);
	printf("Requested File name : %s\n",fileName);
	fd=open(fileName,O_RDONLY);
	
	if(fd==-1){
		strcpy(content,"File doesnt exist");
	}else{
		read(fd,&content,sizeof(content));
	}
	
	len=sendto(sd,content,sizeof(content),0,(struct sockaddr *)&serverStorage,sizeof(serverStorage));
	return 0;
}
