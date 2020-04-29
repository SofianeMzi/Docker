#!/bin/bash
gcc pingpong.c -o pingpong #compilation du code pingpong.c

for image_id in $(docker images --filter=reference=imagenode1 --format "{{.ID}}") #supression de l'image précédente
	do docker rmi -f ${image_id}
done

docker build -t imagenode1 . # création de la nouvelle image imagenode1 à partir du dockerfile 

for container_id in $(docker ps -aqf "name=node1") #supression du conteneur précédent pour éviter un conflit avec le nouveau conteneur qui va être créé 
	do docker rm -f ${container_id} 
done

docker run -it --restart always --name node1 --network mynet -h node1 imagenode1 bash #lancement du conteneur node1 ( l'argument --restart est inutile pour le moment )
#ici, le conteneur est tombé (pour x ou y raison) on lance la procédure de redémarrage

while true; do # boucle qui permet de relancer le conteneur tout de suite après qu'il ait été fermé ( intentionellement ou non)
	start=`date +%s%N | cut -b1-13` #mesure du temps
	for container_id in $(docker ps -aqf "name=node1") #supression du conteneur précédent 
		do docker rm -f ${container_id} 
	done
 #lancement du nouveau  conteneur, avec l'option permettant de rentrer dedans
	docker run --name node1 --network mynet -h node1 imagenode1 bash 
	end=`date +%s%N | cut -b1-13` #mesure du temps
	runtime=$((end-start))
	echo $runtime ms
done 
