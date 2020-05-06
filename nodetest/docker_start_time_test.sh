#!/bin/bash
#permet de réaliser le test du temps de redémarrage ou d'utiliser le conteneur en mode restart

#compilation des codes
gcc pingpong.c -o pingpong  

# création de la nouvelle image imagenodetest à partir du dockerfile 
docker build -t imagenodetest . 

#supression du conteneur précédent pour éviter un conflit avec le nouveau conteneur qui va être créé
for container_id in $(docker ps -aqf "name=nodetest")  
	do docker rm -f ${container_id} 
done 

#lancement du conteneur 
docker run -dt --name nodetest --network mynet -h nodetest imagenodetest bash 
#connecter le conteneur à différent sous-réseau
	docker network connect mynet2 nodetest
	docker network connect mynet3 nodetest
	docker network connect mynet4 nodetest
	docker network connect mynet5 nodetest
	docker network connect mynet6 nodetest
	docker network connect mynet7 nodetest
	docker network connect mynet8 nodetest
	docker network connect mynet9 nodetest
	docker network connect mynet10 nodetest

#ici, le conteneur est tombé (pour x ou y raison) on lance la procédure de redémarrage


# boucle qui permet de relancer le conteneur tout de suite après qu'il ait été fermé ( intentionellement ou non)
i=0
while true; do 
	((i+=1))
	echo le conteneur va être tué...
	docker kill nodetest
	echo le conteneur est mort
	echo redémarrage n°$i
	echo le conteneur va être redémarré
	start=`date +%s%N | cut -b1-13` #mesure du temps
#lancement du conteneur 
	docker start nodetest
	end=`date +%s%N | cut -b1-13` #mesure du temps
	runtime=$((end-start))
	echo Conteneur redémarré en $runtime ms
	
done 
