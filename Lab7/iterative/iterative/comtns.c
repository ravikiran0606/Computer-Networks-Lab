#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<string.h>
#define maxi 100

// Com TLD name Server :

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
	
	strcpy(table[0].name,"amazon");
	table[0].p_n=30198;
	noofdet++;

	strcpy(table[1].name,"google");
	table[1].p_n=30199;
	noofdet++;

}

struct msg getRes(struct msg req){
        int i,j,k;
        int n,m;
        n=strlen(req.e_b);
        int ff;
        struct msg res;
        res.h_l=1;
        strcpy(res.e_b,req.e_b);
        for(i=0;i<noofdet;i++){
                m=strlen(table[i].name);
                for(k=0;k<n;k++){
                        ff=0;
                        for(j=0;j<m;j++){
                                if(k+j>=n || req.e_b[k+j]!=table[i].name[j]){
                                        ff=1;
                                        break;
                                }
                        }
                        if(ff==0){
                                res.p_n=table[i].p_n;
                                goto next;
                        }
                }
        }
        next:
        return res;
}


int main(){
        int sid,bd,ld,size,ad,len;
        sid=socket(AF_INET,SOCK_DGRAM,0);
        struct sockaddr_in comtns;
        struct sockaddr_storage lns;

        comtns.sin_family=AF_INET;
        comtns.sin_port=htons(30195);
        comtns.sin_addr.s_addr=inet_addr("127.0.0.1");

        if(sid==-1){
                printf("\n\n\n\nError in Socket creation");
        }

        bd=bind(sid,(struct sockaddr*)&comtns,sizeof(struct sockaddr));
        if(bd==-1){
                printf("\n\n\n\nbind failed..");
        }
        
	struct msg req,res;
	populate();

        while(1){
                recvfrom(sid,&req,sizeof(req),0,(struct sockaddr *)&lns,&size);
                printf("\n\n\n\nGot Request : %s",req.e_b);
		res=getRes(req);
                sendto(sid,&res,sizeof(res),0,(struct sockaddr *)&lns,size);
		printf("\n\n\n\nSend Response : %d",res.p_n);
        }
        return 0;
}


