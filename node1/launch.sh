#!/bin/bash
gcc serveur.c -o Snode1
gcc sender.c -o sender
gcc pingpong.c -o pingpong

for image_id in $(docker images --filter=reference=imagenode1 --format "{{.ID}}")
	do docker rmi -f ${image_id}
done

docker build -t imagenode1 .

for container_id in $(docker ps -aqf "name=node1")
	do docker rm -f ${container_id} 
done

docker run -it --name node1 --network mynet -h node1 imagenode1 bash
