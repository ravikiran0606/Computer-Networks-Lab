#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define maxi 100

struct msg{
	int h_l;
	int p_n;
	char e_b[maxi];
};

int main(){
        int sid,bd,size,len;
        char buf[maxi];
        sid=socket(AF_INET,SOCK_DGRAM,0);
        if(sid==-1){
                printf("\nError in socket creation");
        }

        struct sockaddr_in lns;
        lns.sin_family=AF_INET;
        lns.sin_port=3019;
        lns.sin_addr.s_addr=inet_addr("127.0.0.1");

        struct msg req,res;

        while(1){
            printf("\nEnter the hostname : ");
            scanf("%s",buf);
		    if(strcmp(buf,"xxx")){
		       break;
		    }
    		req.h_l=0;
    		strcpy(req.e_b,buf);
            sendto(sid,&req,sizeof(req),0,(struct sockaddr *)&lns,sizeof(lns));
            //recvfrom(sid,&res,sizeof(res),0,NULL,NULL);
            //printf("\nThe IP Addresss is : %s",res.e_b);
        }
        return 0;
}

