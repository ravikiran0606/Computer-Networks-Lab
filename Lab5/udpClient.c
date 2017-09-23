#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<netinet/in.h>

int main(){
	int sd,bd,size,len;
	char buf[100],msg[100];
	sd=socket(AF_INET,SOCK_DGRAM,0);
	if(sd==-1){
		printf("\nError in socket creation");
	}

	struct sockaddr_in server;     
	server.sin_family=AF_INET;
	server.sin_port=3019;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");	

	while(1){
		printf("Enter the message : ");
		scanf("%s",msg);
		sendto(sd,msg,sizeof(msg),0,(struct sockaddr *)&server,sizeof(server));
		recvfrom(sd,&buf,sizeof(buf),0,NULL,NULL);
		printf("%s\n",buf);
		if(strcmp(buf,"bye")==0){
			break;
		}
	}
	return 0;
}

