/////multicast
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // for sleep()
#include <time.h>// pour nanosleep
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>//pour gettimeofday()

int main(int argc, char *argv[])
{



	    char* group = "236.0.0.0"; 
	    int port = 1110; 
	    const char *message = "Ping";


	    // Création de la socket udp d'envoi (aller)
	    //
	    int sock_aller = socket(AF_INET, SOCK_DGRAM, 0);
	    if (sock_aller < 0) {
		perror("socket");
		return 1;
	    }
	    printf("socket_aller ready\n");
	    // Définition de l'addresse de réception (multicast group)
	    //
	    struct sockaddr_in addr;
	    memset(&addr, 0, sizeof(addr));
	    addr.sin_family = AF_INET;
	    addr.sin_addr.s_addr = inet_addr(group);
	    addr.sin_port = htons(port);

		char buffer[50];
		int sock_retour;
		struct sockaddr_in server_addr = { 0 };
		
	//Création de la socket de réception de données (retour)
		sock_retour= socket(AF_INET, SOCK_DGRAM, 0);
		if(sock_retour < 0){
		 printf("erreur lors de la création de socket\n");
		 exit(1);
	    }
		

		printf("socket_retour created\n");
	//Création de l'addresse de réception (node1) 
	    	server_addr.sin_family = AF_INET;
	    	server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // toute les adresses possibles
	    	server_addr.sin_port = htons(1110); // numéro du port est : 1110
	//Utilisation de setsockopt() afin de permettre à plusieur socket de se connecter au même port        
		u_int yes = 1;
	    	if (
		setsockopt(
		    sock_aller, SOL_SOCKET, SO_REUSEADDR, (char*) &yes, sizeof(yes)
			) < 0
	    	){
	       		perror("Reusing ADDR failed");
	       		return 1;
	    	}



	    	if(bind(sock_retour, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
			printf("error bind socket\n");
			exit(1);
	    }
	      
	    	printf("waiting...\n");
	    	
		int size = sizeof(server_addr);
	// Définition de la structure pour l'utilisation de nanosleep()
		long time_ns=strtol(argv[1], NULL, 10);//temps en ns, (rentré par l'utilisateur)

		struct timespec time, time2;
		time.tv_sec = 0;
		time.tv_nsec = time_ns;

		struct timeval temps_avant, temps_apres;//Structure pour la mesure du temps d'aller retour
		int j=0; // compteur envoie
		int i=0; //compteur réception

	 while (1) {

		gettimeofday (&temps_avant, NULL);//début du compteur aller-retour
		if(( recvfrom (sock_retour, buffer, (sizeof(buffer) - 1), 0, (struct sockaddr*)&server_addr,  &size)) < 0){ // réception de "pong"
		    printf("pas de réception de message");
		    exit(1);
		}
		i=i+1;
		printf("le message reçu est: %s \n", buffer); 
		int send_to_multicast = sendto(sock_aller, message, strlen(message), 0, (struct sockaddr*) &addr, sizeof(addr));//envoi de données au groupe multicast
		j=j+1;
		gettimeofday (&temps_apres, NULL);//fin du compteur aller-retour
		printf("temps aller-retour données: %ld µs\n", (temps_apres.tv_sec -temps_avant.tv_sec)*1000000 + (temps_apres.tv_usec - temps_avant.tv_usec));//affichage du temps d'aller-retour

		printf("%d envoies, %d réceptions\n", j,i);
		
		if (send_to_multicast < 0) {//s'il y a une erreur pendant l'envoi
		    perror("sendto");
		    return 1;
		}
		int delay_s=nanosleep(&time, &time2);//délai d'attente en seconde 
		if (delay_s<0){
			printf("erreur avec le délai");
			perror("nanosleep");
			return -1;
		}
	     }

	    return 0;
	}
