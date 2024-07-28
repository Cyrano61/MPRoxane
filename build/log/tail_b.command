#! /bin/bash
# ici on peut ecrire des commentaires

# les variables


# debut du script

#chemin d'acces du script
case "$0" in
  */*) cd ${0%/*};;
  *) cd .;;
esac

resize -s 28 98

# lancement du prog
tail -f ./log/engine_1.txt