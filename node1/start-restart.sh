#!/bin/bash
# code permettant de savoir si le conteneur s'est arrêté, d'obtenir l'"exit code", de start et restart le conteneur en mode non intéractif. Pour ouvrir un shell du conteneur, ouvrir un autre terminal et utiliser la commande $docker exec -i node1 bash 
for image_id in $(docker images --filter=reference=imagenode1 --format "{{.ID}}") #supression de l'image précédente
	do docker rmi -f ${image_id}
done

docker build -t imagenode1 . # création de la nouvelle image imagenode1 à partir du dockerfile 

for container_id in $(docker ps -aqf "name=node1") #supression du conteneur précédent pour éviter un conflit avec le nouveau conteneur qui va être créé 
		do docker rm -f ${container_id}
done
#lancement du conteneur
docker run -dt --name node1 --network mynet -h node1 imagenode1 bash 

echo "container running, waiting for exit code"
#attente que le conteneur soit tué 
#cmd_output=$(docker wait node1)
#until [ $cmd_output -lt 0 ] #si l'exit code est supérieur ou égal à 0 ( autrement dit , s'il existe)
#do
	#echo "exit code: $cmd_output"
	#echo "container will restart" 
	#restart du conteneur
	#bash start-restart.sh
#done
#amélioration du code en prévision de l'utilisation de docker checkpoint/commit/expose, utilisation d'une boucle while dans laquelle je peux indiquer de redémarrer le conteneur en utilisant d'autre options de la commande docker run, précédement j'utilisais toujours la même commande
while true
do
#j'attend que la fonction wait détecte la fermeture du conteneur
	cmd_output=$(docker wait node1) 
#j'attend que la fotncion wait() détecte un changement d'état du process créé par docker wait node1
	wait $!  
	echo "container stopped, exit code: $cmd_output"
#supression du conteneur précédent pour éviter un conflit avec le nouveau conteneur qui va être créé
	for container_id in $(docker ps -aqf "name=node1")  
		do docker rm -f ${container_id}
	done
	docker run -dt --name node1 --network mynet -h node1 imagenode1 bash
	echo "container restarted"

done

