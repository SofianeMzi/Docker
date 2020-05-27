Ce node est conçu pour montrer le fonctionnement du dockerfile multistage build. Pour des raisons pratiques (temps de compilation du dockerfile) je ne peux intégrer ce dockerfile aux autres nodes pour le moment. 

J'tilise un simple script de type launch.sh pour compiler le dockerfile, et lancer un conteneur. La seule différence de ce script par rapport aux autres est qu'il contient une étape qui permet la suppression de l'image intermédiaire créée du fait de l'utilisation du multistage build dockerfile.
