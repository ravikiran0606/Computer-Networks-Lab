#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define RNS 3333
#define ANS 4444
int main(){

	int sd1,sd2,i,j;
	char host[1024],ip[1024],file[2000],c[10];
	struct sockaddr_in ins;
	struct sockaddr_in ans;
	int len1=sizeof(ins);
	int len2=sizeof(ans);
	sd1=socket(AF_INET,SOCK_DGRAM,0);       
	ins.sin_family=AF_INET;
	ins.sin_port= RNS ;
	ins.sin_addr.s_addr=INADDR_ANY;

	ans.sin_family=AF_INET;
	ans.sin_port=ANS;
	ans.sin_addr.s_addr=INADDR_ANY;
	sd2=socket(AF_INET,SOCK_DGRAM,0);  

	bind(sd1,(struct sockaddr *)&ins,len1);
	while(1){
		int n=recvfrom(sd1,host,sizeof(host),0,(struct sockaddr *)&ins,&len1);
		if(n<0)
			printf("\nError in recv\n");
                host[n]='\0';

		printf("\nHostname : %s\n",host);

		int flag= (rand()+1) % 2;

		int len=strlen(host);
		for(i=4,j=0;i<len;i++,j++)
		{
			c[j]=host[i];
		}
		printf("\n%s",c);

		if(flag==0){


			FILE *fp=fopen("ins1.txt","r");
			printf("\nFILE 1\n");
			while(!feof(fp)){

				fscanf(fp,"%s",file);
				if(strcmp(c,file)==0){
					fscanf(fp,"%s",ip);
					break;
				}

			}
		}
		else if (flag==1){

			FILE *fp=fopen("ins2.txt","r");
			printf("\nFILE 2\n");

			while(!feof(fp)){

				fscanf(fp,"%s",file);
				if(strcmp(c,file)==0){
					fscanf(fp,"%s",ip);
					break;
				}

			}

		}


		if(ip[0]=='\0')
			strcpy(ip,"ERROR : 404 NOT FOUND");
		printf("\nIP : %s\n",ip);

		sendto(sd2,host,strlen(host),0,(struct sockaddr *)&ans,len2);
		int n1=recvfrom(sd2,ip,sizeof(ip),0,(struct sockaddr *)&ans,&len2);
		if(n<0)
			printf("\nError in recv\n");
		ip[n1]='\0';

		printf("\nIP OF HOSTNAME\n");
		printf("\nIP : %s\n",ip);

		sendto(sd1,ip,strlen(ip),0,(struct sockaddr *)&ins,len1);
		strcpy(ip,"");
		strcpy(host,"");
	}
	return 0;
}
