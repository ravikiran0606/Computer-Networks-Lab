#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define CLIENT 1234
#define ROOT 2222
#include<time.h>
int main(){

	int sd1,sd2,flag=0;
	char host[1024],ip[1024],file[2000];
	struct sockaddr_in lns;
	struct sockaddr_in rns;
	int len1=sizeof(lns);
	int len2=sizeof(rns);
	sd1=socket(AF_INET,SOCK_DGRAM,0); 
	lns.sin_family=AF_INET;
	lns.sin_port= CLIENT ;
	lns.sin_addr.s_addr=INADDR_ANY;

	rns.sin_family=AF_INET;
	rns.sin_port=ROOT;
	rns.sin_addr.s_addr=INADDR_ANY;
	sd2=socket(AF_INET,SOCK_DGRAM,0);  

	bind(sd1,(struct sockaddr *)&lns,len1);
	while(1){

		int n=recvfrom(sd1,host,sizeof(host),0,(struct sockaddr *)&lns,&len1);
		if(n<0)
			printf("\nError in recv\n");
		printf("\nhostname : %s",host);
                host[n]='\0';
              
		FILE *fp=fopen("lns.txt","r");
		while(!feof(fp)){

			fscanf(fp,"%s",file);
			if(strcmp(host,file)==0){
				fscanf(fp,"%s",ip);
				printf("\nIP found in the Local DNS\n");
				flag=1;
				break;
			}

		}
		if(flag==0){
			printf("\nIP not found in local DNS server!\n");
			sendto(sd2,host,strlen(host),0,(struct sockaddr *)&rns,len2);
			int n1=recvfrom(sd2,ip,sizeof(ip),0,(struct sockaddr *)&rns,&len2);
			if(n1<0)
				printf("\nError in recv\n");
			ip[n1]='\0';
			printf("\nIP : %s\n",ip);
			sendto(sd1,ip,strlen(ip),0,(struct sockaddr *)&lns,len1);
			int fp1=open("lns.txt",O_RDWR);
			strcat(host,"\n");
			write(fp1,host,strlen(host));
			strcat(ip,"\n");
			write(fp1,ip,strlen(ip));
		}
   else if(flag==1){
  printf("\nIP : %s\n",ip);
 sendto(sd1,ip,strlen(ip),0,(struct sockaddr *)&lns,len1);

}
		flag=0;
		strcpy(ip,"");
		strcpy(host,"");
	}
	return 0;
}
