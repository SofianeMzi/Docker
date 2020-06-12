#!/bin/bash
#permet de faire de la live migration, attente d'un changement du fichier /nodes/commit qui sera signe de la réception d'un commit de la part d'une machine distante. Lancement d'un conteneur à partir de se commit.

for image_id in $(docker images --filter=reference=commitnodetest --format "{{.ID}}")
	do docker rmi -f ${image_id}
done 

for container_id in $(docker ps -aqf "name=nodetest")
	do docker rm -f ${container_id}
done


inotifywait -e close_write /home/sofiane/Bureau/nodes/commit/commitnodetest.tar #attendre un changement du fichier ~/Bureau/nodes/commit

start='date +
docker load -i /home/sofiane/Bureau/nodes/commit/commitnodetest.tar #permet de recréer l'image à partir du fichier .tar


docker run --name nodetest commitnodetest bash # Lancer un conteneur en mode intéractif à partir de l'image du fichier .tar


