
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
../build/release/Roxane -mode ggs -login CyranoM -passw MDP -h 25 -t 12 ../scripts/fforum-20-39.src



# fin du script
