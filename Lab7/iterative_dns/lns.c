#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>
#include<arpa/inet.h>
#define CLIENT 1234
#define ROOT 2222
#define INS 3333
#define ANS 4444
#include<time.h>
int main(){

        int sd1,sd2,sd3,sd4,i,j,flag=0;
        char host[1024],ip1[1024],file[2000],ip2[1024],ip3[1024],c1[20],c2[20];
        struct sockaddr_in lns;
        struct sockaddr_in rns;
        int len1=sizeof(lns);
        int len2=sizeof(rns);
        struct sockaddr_in ins;
        struct sockaddr_in ans;
        int len3=sizeof(ins);
        int len4=sizeof(ans);
        sd1=socket(AF_INET,SOCK_DGRAM,0);
        lns.sin_family=AF_INET;
        lns.sin_port= CLIENT ;
        lns.sin_addr.s_addr=INADDR_ANY;

        rns.sin_family=AF_INET;
        rns.sin_port=ROOT;
        rns.sin_addr.s_addr=INADDR_ANY;

        ins.sin_family=AF_INET;
        ins.sin_port= INS ;
        ins.sin_addr.s_addr=INADDR_ANY;

        ans.sin_family=AF_INET;
        ans.sin_port= ANS;
        ans.sin_addr.s_addr=INADDR_ANY;

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
                                fscanf(fp,"%s",ip3);
                              printf("\nIP found in the Local DNS\n");
                                flag=1;
                                break;
                        }

                }
                if(flag==0){
                 printf("\nIP not found in local DNS server!\n");
              sd2=socket(AF_INET,SOCK_DGRAM,0);
           bind(sd2,(struct sockaddr *)&rns,len2);
            sendto(sd2,host,strlen(host),0,(struct sockaddr *)&rns,len2);
    int n1=recvfrom(sd2,ip1,sizeof(ip1),0,(struct sockaddr *)&rns,&len2);
                        if(n1<0)
                                printf("\nError in recv\n");
                        ip1[n1]='\0';
                        int l1=strlen(host);
                for(i=l1-3,j=0;i<l1;i++,j++)
                {
                        c1[j]=host[i];
                }

                printf("\nIP of %s : %s\n",c1,ip1);
                close(sd2);
                
              sd3=socket(AF_INET,SOCK_DGRAM,0);
          bind(sd3,(struct sockaddr *)&ins,len3);
         sendto(sd3,host,strlen(host),0,(struct sockaddr *)&ins,len3);
    int n2=recvfrom(sd3,ip2,sizeof(ip2),0,(struct sockaddr *)&ins,&len3);
                        if(n2<0)
                                printf("\nError in recv\n");
                        ip2[n2]='\0';
                         int l=strlen(host);
                for(i=4,j=0;i<l;i++,j++)
                {
                        c2[j]=host[i];
                }

                        printf("\nIP of %s : %s\n",c2,ip2);
               close(sd3);

                 sd4=socket(AF_INET,SOCK_DGRAM,0);
             bind(sd4,(struct sockaddr *)&ans,len4);
            sendto(sd4,host,strlen(host),0,(struct sockaddr *)&ans,len4);
    int n3 = recvfrom(sd4,ip3,sizeof(ip3),0,(struct sockaddr *)&ans,&len4);
                        if(n3<0)
                                printf("\nError in recv\n");
                        ip3[n3]='\0';

                        printf("\nIP of %s : %s\n",host,ip3);
                         
                        int fp1=open("lns.txt",O_RDWR);
                        strcat(host,"\n");
                        write(fp1,host,strlen(host));
                        strcat(ip3,"\n");
                        write(fp1,ip3,strlen(ip3));
                   close(sd4);
                 sendto(sd1,ip3,strlen(ip3),0,(struct sockaddr *)&lns,len1);

                }
   else if(flag==1){
  printf("\nIP : %s\n",ip3);
 sendto(sd1,ip3,strlen(ip3),0,(struct sockaddr *)&lns,len1);

}
                   flag=0;
                strcpy(ip1,"");
                strcpy(ip2,"");
                strcpy(ip3,"");
                strcpy(host,"");
        }
        return 0;
   
}
