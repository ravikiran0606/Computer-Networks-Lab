#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define INS 3333
int main(){

	int sd1,i,j;
	char host[1024],ip[1024],file[2000],c[10];
	struct sockaddr_in ins;
	int len1=sizeof(ins);
	sd1=socket(AF_INET,SOCK_DGRAM,0);       
	ins.sin_family=AF_INET;
	ins.sin_port= INS ;
	ins.sin_addr.s_addr=INADDR_ANY;

	bind(sd1,(struct sockaddr *)&ins,len1);
	while(1){
int n=recvfrom(sd1,host,sizeof(host),0,(struct sockaddr *)&ins,&len1);
		if(n<0)
			printf("\nError in recv\n");
                host[n]='\0';

		printf("\nHostname : %s\n",host);

		int flag= (rand()+1) % 3;

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

                 else if (flag==2){

                        FILE *fp=fopen("ins3.txt","r");
                        printf("\nFILE 3\n");

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
		printf("\nIP of %s : %s\n",c,ip);
	sendto(sd1,ip,strlen(ip),0,(struct sockaddr *)&ins,len1);
		strcpy(ip,"");
		strcpy(host,"");
	}
	return 0;
}
