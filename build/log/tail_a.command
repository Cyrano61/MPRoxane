#! /bin/bash
# ici on peut ecrire des commentaires

# les variables


# debut du script

#chemin d'acces du script
case "$0" in
  */*) cd ${0%/*};;
  *) cd .;;
esac

#resize window
printf "\e[8;39;100t"

# lancement du prog
tail -f engine_0.txt