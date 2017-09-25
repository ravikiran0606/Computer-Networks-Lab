#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define ANS 4444
int main(){

	int sd1,i,j;
	char host[1024],ip[1024],file[2000],c[10];
	struct sockaddr_in ans;
	int len1=sizeof(ans);
	sd1=socket(AF_INET,SOCK_DGRAM,0);    
	ans.sin_family=AF_INET;
	ans.sin_port= ANS ;
	ans.sin_addr.s_addr=INADDR_ANY;

	bind(sd1,(struct sockaddr *)&ans,len1);
	while(1) {      
		int n=recvfrom(sd1,host,sizeof(host),0,(struct sockaddr *)&ans,&len1);
                host[n]='\0';

		printf("\nHOST :%s\n",host);

		if(n<0)
			printf("\nError in recv\n");

		int flag = rand()% 2;

		if(flag==0){


			FILE *fp=fopen("ans1.txt","r");
			printf("\nFILE 1\n");
			while(!feof(fp)){

				fscanf(fp,"%s",file);
				if(strcmp(host,file)==0){
					fscanf(fp,"%s",ip);
					break;
				}

			}
		}
		else if (flag==1){

			FILE *fp=fopen("ans2.txt","r");
			printf("\nFILE 2\n");

			while(!feof(fp)){

				fscanf(fp,"%s",file);
				if(strcmp(host,file)==0){
					fscanf(fp,"%s",ip);
					break;
				}

			}

		}


		if(ip[0]=='\0')
			strcpy(ip,"ERROR : 404 NOT FOUND");
		printf("\nIP : %s\n",ip);
		sendto(sd1,ip,strlen(ip),0,(struct sockaddr *)&ans,len1);
		strcpy(ip,"");
		strcpy(host,"");
	}
	return 0;
}
