#!/bin/bash

#simple script permettant de lancer un conteneur en recréant une nouvelle image (et supprimant l'ancienne) et en supprimant l'ancien conteneur de même nom.

gcc client.c -o Cnode3
gcc receiver.c -o receiver
gcc pingpongR.c -o pingpongR

for image_id in $(docker images --filter=reference=image_name --format "{{.ID}}")
	do docker rmi ${image_id}
done

docker build -t imagenode3 .

for container_id in $(docker ps -aqf "name=node3")
	do docker rm -f ${container_id} 
done

docker run -it --name node3 --network mynet -h node3 imagenode3 bash
