#!/bin/bash
#simple script permettant de lancer un conteneur en recréant une nouvelle image (et supprimant l'ancienne) et en supprimant l'ancien conteneur de même nom. Ce script permet aussi de supprimer l'image intermédiaire créé par le multistage building process.

gcc client.c -o Cnode6
gcc receiver.c -o receiver
gcc pingpongR.c -o pingpongR

for image_id in $(docker images --filter=reference=image_name --format "{{.ID}}")
	do docker rmi ${image_id}
done

docker build -t imagenode6 .

for container_id in $(docker ps -aqf "name=node6")
	do docker rm -f ${container_id} 
done

for image_id in $(docker images --filter "dangling=true" -q --no-trunc) #supression de l'image intermédiaire créée lors du multistage building. 
	do docker rmi -f ${image_id}
done

docker run -it --name node6 --network mynet -h node6 imagenode6 bash
