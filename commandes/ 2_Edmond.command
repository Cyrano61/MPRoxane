
#! /bin/bash
# ici on peut ecrire des commentaires

# les variables


# debut du script

#chemin d'acces du script
cd ${0%/*}

resize -s 21 96

#visualisation des log
open tail_a.command
open tail_b.command

#attente du lancement des tails
sleep 1

# lancement du prog
../build/release/Roxane -mode ggs -login Edmond -passw MDP -h 25 -t 2 ../scripts/fforum-20-39.src



# fin du script

