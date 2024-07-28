
#! /bin/bash
# ici on peut ecrire des commentaires

# les variables


# debut du script
resize -s 21 96

#chemin d'acces du script
cd ${0%/*}

#visualisation des log
open tail_a.command
open tail_b.command

#attente du lancement des tails
sleep 1


# lancement du prog

while true;
do

./Roxane -mode ggs -login Cyrano -passw MDP -h 26 -t 8  ../../fforum-20-39.src

sleep 10

done

# -fixeline D3E3F4G5G4C3F5F6D6F3E6G6G3H4H5H3H2E7D7C8H6F7C4B4C2

# fin du script

