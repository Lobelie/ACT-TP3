Palette (TP3) ACT
Clement DUPONT
Pierre FALEZ

5. La formule pour obtenir les distance minimal est sum((palette[i]-meilleurGris)²*coefficient[i])
	A partir de ceci on peut déduire que pour minimiser cette formule, il faut réduire la différence palette[i]-meilleurGris.
	Pour cela il faut donc choisir des couleurs proches du meilleur gris, en occurrence les couleur voisines.
