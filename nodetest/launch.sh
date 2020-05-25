#!/bin/bash
#simple script permettant de lancer un conteneur en recréant une nouvelle image (et supprimant l'ancienne) et en supprimant l'ancien conteneur de même nom. Ce script permet aussi de supprimer l'image intermédiaire créé par le multistage building process.

for image_id in $(docker images --filter=reference=imagenodetest --format "{{.ID}}") #supression de l'image précédente
	do docker rmi -f ${image_id}
done

docker build -t imagenodetest . # création de la nouvelle image imagenodetest à partir du dockerfile 

for container_id in $(docker ps -aqf "name=nodetest") #supression du conteneur précédent pour éviter un conflit avec le nouveau conteneur qui va être créé 
	do docker rm -f ${container_id} 
done

for image_id in $(docker images --filter "dangling=true" -q --no-trunc) #supression de l'image intermédiaire créée lors du multistage building. 
	do docker rmi -f ${image_id}
done

docker run -it --name nodetest --network mynet -h nodetest imagenodetest bash #lancement du conteneur 
