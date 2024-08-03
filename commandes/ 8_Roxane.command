
#! /bin/bash
# ici on peut ecrire des commentaires

# les variables


# debut du script

#chemin d'acces du script
cd ${0%/*}


#visualisation des log
open ../build/log/tail_a.command
open ../build/log/tail_b.command

#attente du lancement des tails
sleep 1

# lancement du prog
../build/Release/Roxane  -mode ggs -login Roxane -passw Rostand -h 26 -t 8 /Users/caussebruno/Documents/othello/MPRoxane[2024-07-21]/scripts/fforum-20-39.src

# fin du script

