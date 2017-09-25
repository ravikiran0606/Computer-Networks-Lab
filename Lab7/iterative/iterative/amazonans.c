#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<string.h>
#define maxi 100

// Amazon authoritative name Server :

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
	
	strcpy(table[0].name,"www.amazon.com");
	strcpy(table[0].ip,"104.108.218.228");
	noofdet++;

	strcpy(table[1].name,"www.amazonport.com");
	strcpy(table[0].ip,"104.108.218.226");
	noofdet++;


	strcpy(table[2].name,"www.amazonaws.com");
	strcpy(table[0].ip,"104.108.218.227");
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
        struct sockaddr_in aans;
        struct sockaddr_storage lns;

        aans.sin_family=AF_INET;
        aans.sin_port=htons(30198);
        aans.sin_addr.s_addr=inet_addr("127.0.0.1");

        if(sid==-1){
                printf("\n\n\n\nError in Socket creation");
        }

        bd=bind(sid,(struct sockaddr*)&aans,sizeof(struct sockaddr));
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


