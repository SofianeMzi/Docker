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
int main(int argc, char *argv[])
{

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
strcpy(buffer,"Node5: Pong");
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
