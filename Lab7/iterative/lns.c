#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<string.h>
#define maxi 100

struct msg{
        int h_l;
	int p_n;
        char e_b[maxi];
};

int main(){
        int sid,sid2,sid3,sid4,bd,ld,csize,ad,len;

	// As a local name Server...
        sid=socket(AF_INET,SOCK_DGRAM,0);

	// As a client to DNS root server...
	sid2=socket(AF_INET,SOCK_DGRAM,0);

        // As a client to DNS tld server...
        sid3=socket(AF_INET,SOCK_DGRAM,0);
	
        // As a client to DNS authoritative server...
        sid4=socket(AF_INET,SOCK_DGRAM,0);

        struct sockaddr_in lns,rns,tns,ans;
        struct sockaddr_storage client;

	// local name server...
        lns.sin_family=AF_INET;
        lns.sin_port=30191;
        lns.sin_addr.s_addr=inet_addr("127.0.0.1");

	// root name server...
        rns.sin_family=AF_INET;
        rns.sin_port=30192;
        rns.sin_addr.s_addr=inet_addr("127.0.0.1");	

	// tld name server...
        tns.sin_family=AF_INET;
        tns.sin_port=30193;
        tns.sin_addr.s_addr=inet_addr("127.0.0.1");

	// authoritative server...
        ans.sin_family=AF_INET;
        ans.sin_port=30194;
        ans.sin_addr.s_addr=inet_addr("127.0.0.1");
	
        if(sid==-1){
                printf("Error in Socket creation");
        }

        bd=bind(sid,(struct sockaddr*)&lns,sizeof(struct sockaddr));
        if(bd==-1){
                printf("bind failed..");
         }
        struct msg pre,preres,req1,res1,req2,res2,req3,res3;
        while(1){
		
		// Getting request from client...
                recvfrom(sid,&pre,sizeof(pre),0,(struct sockaddr *)&client,&csize);
                printf("\nGot request : %s",pre.e_b);
       
		// Connecting to DNS root server...
		req1.h_l=0;
		strcpy(req1.e_b,pre.e_b);
		sendto(sid2,&req1,sizeof(req1),0,(struct sockaddr *)&rns,sizeof(rns));
		printf("\nSent request : %s",req1.e_b);	
		
		// Getting reply from DNS root server...
		recvfrom(sid2,&res1,sizeof(res1),0,NULL,NULL);
		printf("\nGot Response : %s",res1.e_b);



                // Connecting to DNS tld server...
                req2.h_l=0;
                strcpy(req2.e_b,res1.e_b);
                sendto(sid3,&req2,sizeof(req2),0,(struct sockaddr *)&tns,sizeof(tns));
                printf("\nSent request : %s",req2.e_b);

                // Getting reply from DNS tld server...
                recvfrom(sid3,&res2,sizeof(res2),0,NULL,NULL);
                printf("\nGot Response : %s",res2.e_b);



                // Connecting to DNS authoritative server...
                req3.h_l=0;
                strcpy(req3.e_b,res2.e_b);
                sendto(sid4,&req3,sizeof(req3),0,(struct sockaddr *)&ans,sizeof(ans));
                printf("\nSent request : %s",req3.e_b);

                // Getting reply from DNS authoritative server...
                recvfrom(sid4,&res3,sizeof(res3),0,NULL,NULL);
                printf("\nGot Response : %s",res3.e_b);
	
		// Sending response to client...
		preres.h_l=1;
	        sendto(sid,&preres,sizeof(preres),0,(struct sockaddr *)&client,csize);
                printf("\nSent response : %s",preres.e_b);
        }
        return 0;
}


