#!/bin/bash
# script permettant de réaliser la migration d'un conteneur vers une machine distante.

start=`date +%s%N | cut -b1-13`

for image_id in $(docker images --filter=reference=commitnodetest --format "{{.ID}}") #supression du commit précédent
	do docker rmi -f ${image_id}
done

docker commit -p nodetest commitnodetest # réaliser le commit du conteneur

cd /home/sofian/Bureau/stage-thales/commits

docker save -o commitnodetest.tar commitnodetest #sauvegarder dans un .tar file l’image commitnodetest

scp -rP 2222 commitnodetest.tar sofiane@127.0.0.1:/home/sofiane/Bureau/nodes/commit #transfère du fichier de commit de la machine hôte vers hostC

end=`date +%s%N | cut -b1-13`
runtime=$((end-start))
echo $runtime ms 
