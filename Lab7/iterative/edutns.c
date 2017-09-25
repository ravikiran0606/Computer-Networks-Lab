#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<string.h>
#define maxi 100

// Root name Server :

struct msg{
        int h_l;
	int p_n;
        char e_b[maxi];
};	

struct det{
	char name[maxi];
	int p_n;
}table[maxi];

int noofdet=0;

void populate(){
	
	strcpy(table[0].name,"com");
	table[0].p_n=30195;
	noofdet++;

	strcpy(table[1].name,"edu");
	table[1].p_n=30196;
	noofdet++;


	strcpy(table[2].name,"org");
	table[2].p_n=30197;
	noofdet++;
}

struct msg getRes(struct msg req){
	int i;
	
}

int main(){
        int sid,bd,ld,size,ad,len;
        sid=socket(AF_INET,SOCK_DGRAM,0);
        struct sockaddr_in rns;
        struct sockaddr_storage lns;

        rns.sin_family=AF_INET;
        rns.sin_port=3019;
        rns.sin_addr.s_addr=inet_addr("127.0.0.1");

        if(sid==-1){
                printf("Error in Socket creation");
        }

        bd=bind(sd,(struct sockaddr*)&server,sizeof(struct sockaddr));
        if(bid==-1){
                printf("bind failed..");
        }
        
	struct msg req,res;

        while(1){
                recvfrom(sid,&req,sizeof(req),0,(struct sockaddr *)&lns,&size);
                printf("Got Request : %s",req.e_b);
		res=getRes(req);
                sendto(sid,&res,sizeof(res),0,(struct sockaddr *)&lns,size);
		printf("Send Response : %s",);
        }
        return 0;
}


