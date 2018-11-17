# Wolf3D

Inspired by the world-famous 90's game of similar naming (which was the first FPS ever). Explore the technique of ray-casting. The goal is to create a dynamic view inside of a maze. How far will you go to create the best game we have ever seen?

Work in progress

from:</br>
banthony</br>
grdalmas</br>
jlobjois consultant en mathématique</br>

# Install and Run (MacOS & Linux only)
`git clone https://github.com/banthony42/Wolf3D.git`</br>
</br>
`cd Wolf3D`</br>
</br>
`git clone https://github.com/banthony42/libft.git`</br>
</br>
`make`</br>
</br>
`./wolf3D ./map/...`

Le pacakge xorg est requis


# Bugs connus
Game:
  Les fps chutes en mode non texturé, lorsque l'on se rapproche des murs.

Linux:
  La transparence ne fonctionne pas car la palette de couleur pour la fenêtre est en 24bit au lieu de 32bit.
  A tester sur différente machines linux pour valider le bug.
