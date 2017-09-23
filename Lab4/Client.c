#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<stdlib.h>
#define MAXSIZE 100


struct msg_packet{
	int h_l;
	int e_b[MAXSIZE];
};

int main(int argc,char* argv[]){
	int csockid;
	char buf[MAXSIZE],buf2[MAXSIZE];
	struct sockaddr_in caddr;
	struct msg_packet msg;
	int bytes;

	csockid= socket(AF_INET,SOCK_STREAM,0);
	printf("Client Sock id = %d\n",csockid);

	if(csockid < 0){
		printf("Socket Error");
		return 0;
	}

	caddr.sin_port=htons(3019);
	caddr.sin_family=AF_INET;
	caddr.sin_addr.s_addr=inet_addr("127.0.0.1");

	if( connect(csockid,(struct sockaddr*) &caddr,sizeof(struct sockaddr) )==-1){
		printf("Error Connecting");
		return 0;
	}	 

	int choice,num;
	printf("\nChoices : 1) Date 2) Time 3) Factorial\n");	
	while(1){
		printf("Enter any choice. ");
		scanf("%d",&choice);
		
		if(choice == 1){
			msg.h_l = 1;
			if ( send(csockid,&msg,sizeof(msg),0) == -1){
				printf("Error Sending.\n");
				return 0;
			}

			if( (bytes = recv(csockid,&msg,sizeof(msg),0) ) == -1){
				printf("Error Receiving.\n");
				return 0;
			}

			printf("Date : %d/%d/%d\n",msg.e_b[0]+1900,msg.e_b[1]+1,msg.e_b[2]);
		}
		else if(choice == 2){
			msg.h_l = 2;
			if ( send(csockid,&msg,sizeof(msg),0) == -1){
                                printf("Error Sending.\n");
                                return 0;
                        }

                        if( (bytes = recv(csockid,&msg,sizeof(msg),0) ) == -1){
                                printf("Error Receiving.\n");
                                return 0;
                        }

                        printf("Time : %d:%d:%d\n",msg.e_b[0],msg.e_b[1],msg.e_b[2]);

		}
		else if(choice == 3){
			msg.h_l = 3;
			printf("Enter the number. ");
			scanf("%d",&num);
			msg.e_b[0]=num;
			
			if ( send(csockid,&msg,sizeof(msg),0) == -1){
                                printf("Error Sending.\n");
                                return 0;
                        }

                        if( (bytes = recv(csockid,&msg,sizeof(msg),0) ) == -1){
                                printf("Error Receiving.\n");
                                return 0;
                        }

                        printf("The Factorial of the number is %d\n",msg.e_b[1]);			
		}
		else if(choice == 4){
			msg.h_l = 4;
			if ( send(csockid,&msg,sizeof(msg),0) == -1){
                                printf("Error Sending.\n");
                                return 0;
                        }
			close(csockid);
			break;
		}
		else{
			printf("Enter a valid choice.\n");
		}
	}
	
	return 0;
}

