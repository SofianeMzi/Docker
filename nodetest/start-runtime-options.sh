#!/bin/bash

#script permettant de démarrer un conteneur avec des runtimes options (nombre de cpu utilisé, mémoire attribuée, part de cpu utilisé etc...)

for image_id in $(docker images --filter=reference=imagenodetest --format "{{.ID}}") #supression de l'image précédente
	do docker rmi -f ${image_id}
done

docker build -t imagenodetest . # création de la nouvelle image imagenode1 à partir du dockerfile 

for container_id in $(docker ps -aqf "name=nodetest") #supression du conteneur précédent pour éviter un conflit avec le nouveau conteneur qui va être créé 
	do docker rm -f ${container_id} 
done

docker run -it --name nodetest --network mynet -h nodetest --cpuset-cpus=0,1 --cpus=2 --cap-add=sys_nice --cpu-rt-runtime=950000 --ulimit rtprio=99 imagenodetest bash #lancement du conteneur 
