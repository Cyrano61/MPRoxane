
#! /bin/bash
# ici on peut ecrire des commentaires

# les variables


# debut du script

#chemin d'acces du script
cd ${0%/*}

#visualisation des log
open tail_a.command

#attente du lancement des tails
sleep 1


# lancement du prog
./Roxane -h 24 -t 2 -useSleepingThreads ../../nulles-difficiles.script

# fin du script

