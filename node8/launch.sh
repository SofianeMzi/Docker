#!/bin/bash
gcc client.c -o Cnode8
gcc receiver.c -o receiver
gcc pingpongR.c -o pingpongR

for image_id in $(docker images --filter=reference=image_name --format "{{.ID}}")
	do docker rmi ${image_id}
done

docker build -t imagenode8 .

for container_id in $(docker ps -aqf "name=node8")
	do docker rm -f ${container_id} 
done

docker run -it --name node8 --network mynet -h node8 imagenode8 bash
