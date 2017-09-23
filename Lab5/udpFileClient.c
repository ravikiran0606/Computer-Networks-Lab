#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>

int main(){
	
	int sd,bd,ld,size,ad,cd,fd,flag=0;
	char fileName[100],content[1000];
	sd=socket(AF_INET,SOCK_DGRAM,0);

	printf("Socket id : %d\n",sd);
	struct sockaddr_in server;     
	server.sin_family=AF_INET;
	server.sin_port=3019;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	printf("Enter the file name : ");
	scanf("%s",fileName);
	sendto(sd,fileName,sizeof(fileName),0,(struct sockaddr *)&server,sizeof(server));
	recvfrom(sd,&content,sizeof(content),0,NULL,NULL);
	printf("Contents : %s",content);
	return 0;
}

