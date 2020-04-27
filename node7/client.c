#include<stdio.h>      
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
#include <stdlib.h>
#include <string.h>
#define PORT 1110
int main()
{    
   
    	SOCKET sock;       
        SOCKADDR_IN sin;
       
    	sin.sin_family=AF_INET;
        sin.sin_addr.s_addr=inet_addr("172.18.0.1");
        sin.sin_port=htons(PORT);
       
        sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

        bind(sock,(SOCKADDR*)&sin,sizeof(sin));

        if(connect(sock,(SOCKADDR*)&sin,sizeof(sin)) == SOCKET_ERROR)
        {
                printf("La connexion a échouée\n");
                exit(0);
        }
        char buffer[50];
        memset(buffer,0,sizeof(buffer));
        int err=0;
        printf("Connexion du node 7 au node 1 en attente \n\n\n");
        while(err>-1)
        {

		/*printf("\n*********** Attente d'une reponse du node 1 ***********\n");
                err=recv(sock,buffer,sizeof(buffer),0);
                printf("Serveur : %s\n\n",buffer);
                memset(buffer,0,sizeof(buffer));
                sleep(1);
                printf("*********** A vous de parler ***********\nVous :");
        	strcpy(buffer, "pong");
                err=send(sock,buffer,sizeof(buffer),0);
                memset(buffer,0,sizeof(buffer));
		sleep(1);*/

		printf("\n*********** Attente d'une réponse du node 1 ***********\n");
                err=recv(sock,buffer,sizeof(buffer),0);
                printf("Node1 : %s\n\n",buffer);
                memset(buffer,0,sizeof(buffer));
                printf("Message envoyé...\n");
        	strcpy(buffer, "pong");
                err=send(sock,buffer,sizeof(buffer),0);
                memset(buffer,0,sizeof(buffer));
        }
        printf("Connexion terminée\n\n");
}
