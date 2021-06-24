# ProjetMajeur
Bienvenue au projet xSmartFireKiller2000.
Membres du projet : Lucas PHILIPPE, Manea MAZELLIER, Lucas CHAUVIGNE, Judickaelle PELLETIER, Martin RAIMBAULT, Flavien COMET.



Ce GitHub contient 4 dossiers différents :

- Arduino
  1) NodeMcvtest : Code pour l'arduino pour utiliser son module WiFi (test)
  2) Temp_fumee : Code pour le détecteur de fumée et le capteur d'humidité/température. Il permet de faire changer de couleur la Led lors d'un incident.
  3) detecteurMQ : Code pour lancer l'alarme sonore en fonction de la couleur de la Led.
  4) dht11 : Code pour calculer la température et le taux d'humidité ressenti.
  5) wificam : Code pour utiliser une caméra (ESP32-CAM) et envoie l'image capturée sur un serveur.
  6) DHTlib.zip : librairies pour le capteur dht11.

- Python
  1) xSmart.py : Script permettant de se connecter à la base de donnée. Il permet de lire les données envoyées par les capteurs. Si elles sont dans un format correct, elles sont enregistrées dans la base de données.

- bdd sql
  1) data.sql : Script pour créer les tables de la base de données.
  2) user.sql : Script pour créer la table des utilisateurs.
  3) xsmartfirekiller.sql : Script pour créer les tables propres aux incidents.

- projet_majeur
 Dossier comportant tous les fichiers de l'interface Web créée via HTML, CSS et Symfony.
  1) templates : structures des pages en HTML.twig.
  2) src : Fichiers relatifs au backend de l'interface WEB (en php).
 
 
 
PARTIE CYBER : 
Pour la partie sécurisation de notre objet et du réseau, nous avons divisé le travail en 4 parties :

- ftp
  1) Authentification par clé
  2) Changement de port de connexion
  3) Création d'un utilisateur unique
  4) Autoriser l'accès à un seul dossier
  5) Créer un nombre maximal de connexions

- ssh
  1) Authentification par clé
  2) Changement de port de connexion
  3) Empêcher la connexion Root
  4) Créer un nombre maximal de connexions

- Apache2
  1) Limiter les attaques DoS dans le dossier apache2.conf
  2) Limiter les informations visibles (version apache, php...)
  3) Empêcher le parcours des répertoires avec l'option "Indexes"
  4) Empêcher l'utilsiation de liens symboliques avec l'option "FollowSymLinks"
  5) Gérer l'accès des fichiers .htaccess

- Fail2ban
  1) installer le service Fail2ban
  2) Configurer le fichier jail.local
  3) Ajouter les ports utilisés pour ssh, ftp et apache2
 
