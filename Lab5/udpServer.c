#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<string.h>

int main(){
	int sd,bd,ld,size,ad,len;
	sd=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in server;
	struct sockaddr_in client;	
	struct sockaddr_storage serverStorage;

	server.sin_family=AF_INET;
	server.sin_port=3019;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if(sd==-1){
		printf("Error in Socket creation");
	}
		
	bd=bind(sd,(struct sockaddr*)&server,sizeof(struct sockaddr));
	if(bd==-1){
		printf("bind failed..");
	 }
	char msg[100],buf[100];
	while(1){			
		recvfrom(sd,&buf,sizeof(buf),0,(struct sockaddr *)&serverStorage,&size);
		printf("%s\n",buf);
		printf("Enter message : ");
		scanf("%s",msg);
		sendto(sd,msg,sizeof(msg),0,(struct sockaddr *)&serverStorage,size);
		if(strcmp(msg,"bye")==0){
			break;
		}
	}
	return 0;
}

