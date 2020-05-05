#!/bin/bash
#permet de réaliser le test du temps de redémarrage ou d'utiliser le conteneur en mode restart

#compilation des codes
gcc pingpong.c -o pingpong  

#supression de l'image précédente
for image_id in $(docker images --filter=reference=imagenodetest --format "{{.ID}}") 
	do docker rmi -f ${image_id}
done

# création de la nouvelle image imagenode1 à partir du dockerfile 
docker build -t imagenodetest . 

#supression du conteneur précédent pour éviter un conflit avec le nouveau conteneur qui va être créé
for container_id in $(docker ps -aqf "name=node1")  
	do docker rm -f ${container_id} 
done

#lancement du conteneur nodetest ( l'argument --restart est inutile pour le moment )
docker run -it --restart always --name nodetest --network mynet -h nodetest imagenodetest bash 

#ici, le conteneur est tombé (pour x ou y raison) on lance la procédure de redémarrage


# boucle qui permet de relancer le conteneur tout de suite après qu'il ait été fermé ( intentionellement ou non)
while true; do 
	start=`date +%s%N | cut -b1-13` #mesure du temps
#supression du conteneur précédent 
	for container_id in $(docker ps -aqf "name=nodetest") 
		do docker rm -f ${container_id} 
	done
#lancement du nouveau  conteneur
	docker run --name nodetest --network mynet -h nodetest imagenodetest bash #ligne a décommenter si on souhaite réaliser le test du temps de redémarrage

#connecter le conteneur à différent sous-réseau
	docker network connect mynet2 nodetest
	docker network connect mynet3 nodetest
	docker network connect mynet4 nodetest
	docker network connect mynet4 nodetest
	docker network connect mynet5 nodetest
	docker network connect mynet6 nodetest
	docker network connect mynet7 nodetest
	docker network connect mynet8 nodetest
	docker network connect mynet9 nodetest
	docker network connect mynet10 nodetest
	#docker run -it --name node1 --network mynet -h node1 imagenode1 bash #ligne a décommenter si l'on souhaite se servir de ce code pour utiliser le conteneur et le relancer s'il automatiquement s'il crash 
	end=`date +%s%N | cut -b1-13` #mesure du temps
	runtime=$((end-start))
	echo $runtime ms
done 
