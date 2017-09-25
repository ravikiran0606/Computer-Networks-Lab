#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<string.h>
#define maxi 100

// Google authoritative name Server :

struct msg{
        int h_l;
	int p_n;
        char e_b[maxi];
};	

struct det{
	char name[maxi];
	char ip[maxi];
}table[maxi];

int noofdet=0;

void populate(){
	
	strcpy(table[0].name,"www.google.com");
	strcpy(table[0].ip,"216.58.220.36");
	noofdet++;

	strcpy(table[1].name,"www.googlemail.com");
	strcpy(table[0].ip,"216.58.220.34");
	noofdet++;


	strcpy(table[2].name,"www.onedrivegoogle.com");
	strcpy(table[0].ip,"216.58.220.35");
	noofdet++;
}

struct msg getRes(struct msg req){
	int i;
	struct msg res;
	res.h_l=1;
	for(i=0;i<noofdet;i++){
		if(strcmp(req.e_b,table[i].name)==0){
			strcpy(res.e_b,table[i].ip);
			break;
		}
	}	
	return res;
}

int main(){
        int sid,bd,ld,size,ad,len;
        sid=socket(AF_INET,SOCK_DGRAM,0);
        struct sockaddr_in gans;
        struct sockaddr_storage lns;

        gans.sin_family=AF_INET;
        gans.sin_port=htons(30199);
        gans.sin_addr.s_addr=inet_addr("127.0.0.1");

        if(sid==-1){
                printf("\n\n\n\nError in Socket creation");
        }

        bd=bind(sid,(struct sockaddr*)&gans,sizeof(struct sockaddr));
        if(bd==-1){
                printf("\n\n\n\nbind failed..");
        }

	populate();        
	struct msg req,res;

        while(1){
                recvfrom(sid,&req,sizeof(req),0,(struct sockaddr *)&lns,&size);
                printf("\n\n\n\nGot Request : %s",req.e_b);
		res=getRes(req);
                sendto(sid,&res,sizeof(res),0,(struct sockaddr *)&lns,size);
		printf("\n\n\n\nSend Response : %s",res.e_b);
        }
        return 0;
}


