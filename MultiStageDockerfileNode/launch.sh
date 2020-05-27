#!/bin/bash
#simple script permettant de lancer un conteneur en recréant une nouvelle image (et supprimant l'ancienne) et en supprimant l'ancien conteneur de même nom.

for image_id in $(docker images --filter=reference=imagemsnode --format "{{.ID}}") #supression de l'image précédente
	do docker rmi -f ${image_id}
done

docker build -t imagemsnode . # création de la nouvelle image imagenodetest à partir du dockerfile 

for container_id in $(docker ps -aqf "name=nodems") #supression du conteneur précédent pour éviter un conflit avec le nouveau conteneur qui va être créé 
	do docker rm -f ${container_id} 
done

for image_id in $(docker images --filter=reference=<none> --format "{{.ID}}") #supression de l'image précédente
	do docker rmi -f ${image_id}
done


docker run -it --name nodems --network mynet -h nodems imagemsnode bash #lancement du conteneur 
