
#! /bin/bash
# ici on peut ecrire des commentaires

# les variables


# debut du script

#chemin d'acces du script
cd ${0%/*}

#visualisation des log
open ../build/log/tail_a.command

#attente du lancement des tails
sleep 1


# lancement du prog
../build/Release/Roxane -h 25 -t 12 /Users/caussebruno/Documents/othello/MPRoxane[2024-07-21]/scripts/fforum-60-79.src

# fin du script

