#!/bin/bash
#Script permettant de créer l'image intermédiare centos avec le compilateur gcc, nécessaire au multistage build DOCKERFILE

for image_id in $(docker images --filter=reference=centos_gcc --format "{{.ID}}") #supression de l'image précédente
	do docker rmi -f ${image_id}
done

docker build -t centos_gcc . # création de l'image intermédiaire par compilation du dockerfile 


