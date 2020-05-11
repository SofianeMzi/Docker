#!/bin/bash
# Code permettant de lancer un conteneur, lancer l'application pingpong, attendre le crash du conteneur, relancer le conteneur et l'application automatiquement. Ce code contient un compteur de redémarrage ainsi que le temps de redémarrage du SERVICE (= de l'application pingpong)

for image_id in $(docker images --filter=reference=imagenodetest --format "{{.ID}}") #supression de l'image précédente
	do docker rmi -f ${image_id}
done

docker build -t imagenodetest . # création de la nouvelle image imagenodetest à partir du dockerfile 

for container_id in $(docker ps -aqf "name=nodetest") #supression du conteneur précédent pour éviter un conflit avec le nouveau conteneur qui va être créé 
		do docker rm -f ${container_id}
done
#lancement du conteneur et de l'application pingpong 
docker run -dt --name nodetest --network mynet -h nodetest imagenodetest ./pingpongR multi
docker network connect mynet2 nodetest
docker network connect mynet3 nodetest
docker network connect mynet4 nodetest
docker network connect mynet5 nodetest
docker network connect mynet6 nodetest
docker network connect mynet7 nodetest
docker network connect mynet8 nodetest
docker network connect mynet9 nodetest
docker network connect mynet10 nodetest

echo "container running, waiting for exit code"
#attente que le conteneur soit tué 
i=0 #pour le compteur de redémarrage
while true
do
	((i+=1)) #incrémentation du compteur
#j'attend que la fonction wait détecte la fermeture du conteneur
	cmd_output=$(docker wait nodetest) 
#j'attend que la fotncion wait() détecte un changement d'état du process créé par "docker wait nodetest"
	wait $!  
	echo "container stopped, exit code: $cmd_output"
	echo "container & application restart n°$i"
	
#restart du conteneur en utilisant "docker start"
	start=`date +%s%N | cut -b1-13` #mesure du temps
	docker start nodetest
	end=`date +%s%N | cut -b1-13` #mesure du temps
	runtime=$((end-start))
	echo "container & application restarted in $runtime ms"

done

