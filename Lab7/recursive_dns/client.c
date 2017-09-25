#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define CLIENT 1234
int main(){

        int sd;
        char host[1024],ip[1024];
        struct sockaddr_in client;
        int addrlen=sizeof(client);
        sd=socket(AF_INET,SOCK_DGRAM,0);
        client.sin_family=AF_INET;
        client.sin_port= CLIENT;
        client.sin_addr.s_addr=INADDR_ANY;
        printf("\nEnter the url : ");
        scanf("%s",host);
         printf("\nHOST : %s\n",host);
int n= sendto(sd,host,sizeof(host),0,(struct sockaddr*)&client,addrlen);
if(n<0)
 printf("\nError in send\n");  
int bytes=recvfrom(sd,ip,sizeof(ip),0,(struct sockaddr*)&client,&addrlen);
ip[bytes]='\0';
printf("\nIP : %s\n",ip);
return 0;
}
