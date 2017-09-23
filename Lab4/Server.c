#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<time.h>
#define MAXSIZE 100

struct msg_packet{
	int h_l;
	int e_b[MAXSIZE];
};

int main(){
	int sockid,sockid2,bytes,bytes2;
	int flag=0;
	char buf[MAXSIZE],buf2[MAXSIZE];
	struct sockaddr_in server,client;
	struct tm tvar;
	time_t t = time(NULL);
	tvar = *localtime(&t);
	struct msg_packet msg;

	int len=sizeof(struct sockaddr);

	sockid = socket(AF_INET,SOCK_STREAM,0);

	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(3019);
	server.sin_family=AF_INET;
	
	printf("Sock id = %d\n",sockid);
	
	int bno = bind(sockid, (struct sockaddr*) &server, sizeof(struct sockaddr) );
	printf("Bind return val = %d\n",bno);
	
	int lno = listen(sockid,5);
	printf("Listen return val = %d\n",lno);

	sockid2=accept(sockid,(struct sockaddr*) &client,&len);
	printf("Got Connection from Client sock id = %d\n",sockid2);		

	int choice;
	while(1){
		if(( bytes2 = recv(sockid2,&msg,sizeof(msg),0) ) == -1){
			printf("Error Receiving.\n");
			return 0;
		} 
		choice = msg.h_l;
		if(choice == 1){
			msg.e_b[0] = tvar.tm_year;
			msg.e_b[1] = tvar.tm_mon;
			msg.e_b[2] = tvar.tm_mday;
			
			if( send(sockid2,&msg,sizeof(msg),0) == -1){
				printf("Error Sending.\n");
				return 0;
			}

		}
		else if(choice == 2){
			msg.e_b[0] = tvar.tm_hour;
			msg.e_b[1] = tvar.tm_min;
			msg.e_b[2] = tvar.tm_sec;
			
			if( send(sockid2,&msg,sizeof(msg),0) == -1){
                                printf("Error Sending.\n");
                                return 0;
                        }
		}
		else if(choice == 3){
			int i,ans = 1;
			for(i=2;i<=msg.e_b[0];i++){
				ans*=i;
			}
			msg.e_b[1] = ans;
			
			if( send(sockid2,&msg,sizeof(msg),0) == -1){
                                printf("Error Sending.\n");
                                return 0;
                        }
		}
		else{
			break;
		}
	}
		
	close(sockid2);

	return 0;
}
