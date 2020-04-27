//multicast

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MSGBUFSIZE 256
#include <unistd.h>

//unicast

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

int main(int argc, char *argv[])
{
if(argc != 2){
	printf("Vous devez rentrer un argument\n");
	printf("'uni' pour une communication en unicast");
	printf("'multi' pour une communication en multicast");
	return 0;
}

char *argument=argv[1];
if ( strcmp(argument,"multi")==0){//Si l'argument est multi, alors on fait de l'udp
        char* group = "236.0.0.0"; 
    int port = 1110; 


    // création de la socket udp de réception (aller)
    //
    int sock_aller = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_aller < 0) {
        perror("socket");
        return 1;
    }
printf("socket_aller ready\n");

    // Permettre l'utilisation du même port par plusieur socket 
    //
    u_int yes = 1;
    if (
        setsockopt(
            sock_aller, SOL_SOCKET, SO_REUSEADDR, (char*) &yes, sizeof(yes)
        ) < 0
    ){
       perror("Reusing ADDR failed");
       return 1;
    }

        // définition de l'adresse et du port de réception (node 2à8)
    //
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // permettre à n'importe quelle addresse enregistrées sur le groupe multicast de recevoir les données 
    addr.sin_port = htons(port);

    // bind 
    //
    if (bind(sock_aller, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
        perror("bind");
        return 1;
    }

    // Utilisation de setsocketopt() afin de créer un groupe multicast et de permettre à sock_aller d'y accéder
    //
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(group);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if (
        setsockopt(
            sock_aller, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*) &mreq, sizeof(mreq)
        ) < 0
    ){
        perror("setsockopt");
        return 1;
    }

char buffer[50];
struct sockaddr_in sin;
// Définition du port et de l'adresse de réception (node1) pour l'envoi de données (retour)  
sin.sin_family = AF_INET;
sin.sin_port = htons(1110);
sin.sin_addr.s_addr = inet_addr("172.18.0.1");
// Création d'une deuxième socket pour le retour
int sock_retour = socket(AF_INET, SOCK_DGRAM, 0);
if( sock_retour < 0){
	printf("error client\n");
        exit(1);
    }
      
printf("socket_retour ready\n");
int to = sizeof(sin);
strcpy(buffer,"Node4: Pong");
    while (1) {

	while(sendto(sock_retour, buffer, strlen(buffer), 0, (struct sockaddr*)&sin, to)> 0){//envoi de "pong" par l'intermédiaire de la socket retour
        	printf("le message : %s à été envoyé\n",buffer);
		char msgbuf[MSGBUFSIZE];
        	int addrlen = sizeof(addr);
        	int recv_from_node1 = recvfrom(sock_aller, msgbuf, MSGBUFSIZE, 0, (struct sockaddr *) &addr, &addrlen); // réception de ping par l'intermédiaire de la socket aller
        	if (recv_from_node1 < 0) {
            	perror("recvfrom");
            	return 1;
        	}
        	msgbuf[recv_from_node1] = '\0';
        	puts(msgbuf);
    		}
    	
     }

    return 0;
}
else(strcmp(argument,"uni")==0);// Si l'argument est "uni" alors on fait du tcp
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
        printf("Connexion du node 4 au node 1 en attente \n\n\n");
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
}
