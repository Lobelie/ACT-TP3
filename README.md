Palette (TP3) ACT
Clement DUPONT
Pierre FALEZ

Fichiers :
	image: contient les fonctions permettant de reconstruire et d'enregistrer une image au format PGM (P5 binaire)
	image_reader: contient les fonction pour lire une image au format PGM (P5 binaire et P2 ASCII)
	palette: contient les fonctions pour construire une palette a partir d'une image, ceux pour reduire le nombre de couleur d'une palette et pour retrouver le backtrace de cette derniere, et les fonctions de calcule de meilleurGris et distanceMin 

reduce_palette : équation de récurrence = distanceMin(palette, i, j)+reduce_palette(palette, j, k-1)
		

5. La formule pour obtenir les distance minimal est sum((palette[i]-meilleurGris)²*coefficient[i])
	A partir de ceci on peut déduire que pour minimiser cette formule, il faut réduire la différence palette[i]-meilleurGris.
	Pour cela il faut donc choisir des couleurs proches du meilleur gris, en occurrence les couleur voisines.
