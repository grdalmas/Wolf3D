/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_constante.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:53:57 by banthony          #+#    #+#             */
/*   Updated: 2018/09/12 20:45:46 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_CONSTANTE_H
# define WOLF_CONSTANTE_H

/*
**	Message d'Erreur
*/
# define ERR_MAP "Error: Invalid Map, run the executable alone for help."
# define ERR_OPEN "Error: While openning the file"
# define ERR_CLOSE "Error: While closing the file"
# define ERR_IMG "Error: While creating new image"
# define ERR_TEXTURE "Error: While loading texture"
# define ERR_DOOR "Error: Too many doors in the map file"
# define ERR_DOOR_PLACEMENT "Error: A door is misplaced or badly surrounded at "
# define ERR_QUIT "Wolf3D can't continue further."

/*
**	Usage
*/
# define KEY_1 "move:\tW/A/S/D\nLook:\tRight/Left Arrow\nSneak:\tC\n"
# define KEY_2 "Jump:\tSPACEBAR\nMap:\tTAB\nUse:\tE\nTexture:F1\n"
# define KEY_3 "Run:\tLEFT SHIFT\n"
# define HELP_1 "0:\tsol.\n1:\tstone.\n2:\twood.\n3:\tredbrick.\n4:\tporte.\n"
# define HELP_2 "5:\tpurplestone.\n6:\teagle wall.\n7:\tmossy.\n"
# define HELP_3 "8:\tbluestone.\n9:\tcolorstone.\n;:\tspawn.\n"
# define QUIT "User exit"
# define MC_USAGE "Delete:\t\tReset map.\nV:\t\tBuild an empty valid map.\n"
# define MC_USAGE2 "C + clic:\tDraw a column.\nD + clic:\tDraw a line.\n"

/*
** Calcul d'un pourcentage p sur la valeur x
*/
# define PERCENTAGE(p, x) ((p * x) / 100)

/*
**	Taille fenetre & ecran du jeu
*/
# ifdef __APPLE__
#  define WIN_W 1024
#  define WIN_H 768
# else
#  define WIN_W 800
#  define WIN_H 600
# endif
# define WIN_NAME "Wolf3D"
# define CENTERWIN_W(x) (WIN_W - x) / 2
# define CENTERWIN_H(y) (WIN_H - y) / 2

/*
** Taille Interface Joueur
*/
# define INTRF_W WIN_W
# define INTRF_H PERCENTAGE(17, WIN_H)
# define CENTERINTRF_W(x) (INTRF_W - x) / 2
# define CENTERINTRF_H(y) (INTRF_H - y) / 2

/*
**	Taille ecran map creator
*/
# define MAP_CRT_W WIN_W
# define MAP_CRT_H WIN_H - INTRF_H
# define CENTERSCR_W(x) (MAP_CRT_W - x) / 2
# define CENTERSCR_H(y) (MAP_CRT_H - y) / 2

/*
**	Taille Interface map - Overlay mini map et Ecran de dessin du map creator.
*/
# define MAPI_W PERCENTAGE(70, MAP_CRT_W)
# define MAPI_H PERCENTAGE(70, MAP_CRT_H)
# define CENTERMAPI_W(x) (MAPI_W - x) / 2
# define CENTERMAPI_H(y) (MAPI_H - y) / 2

/*
**	Parsing
**	WALL:	Definit les caracteres etant des murs
*/
# define WALL "12356789"
# define EMPTY_BLOC "0;"

/*
**	Wolf3D
**	MAP_MIN:	Taille minimum d'une map
**	MAP_MAX:	Taille maximum d'une map
**	FOV:		Angle de vue de la cameras, champ de vision.
**	BLOC_SIZE:	Taille d'un mur, ou d'un cube dans le monde
**	PLAYER_RADIUS: Rayon du cercle de la hit_box du joueur.
*/
# define MAP_MIN 3
# define MAP_MAX 500
# define FOV 60
# define BLOC_SIZE 64
# define HALF_BLOC 32
# define MAX_DOOR 32
# define PLAYER_RADIUS 10
# define RANGE 64
# define JUMP_VELOCITY 450
# define GRAVITY 1500
# define FOG_MIN 10
# define SPD_MOVE 200.0
# define SPD_ANGLE 80.0

/*
**	Menu Principal
*/
# define G_NAME "WOLF 3-D"
# define G_RUN "Game"
# define G_MC "Map Creator"
# define G_EXIT "Exit"

/*
**	Map Creator
**	TEXT:				Nombre de texture dans la palette.
**	TEXT_P:				Ecart en pixel, (le pas) entre chaque box de texture.
**	ITEM_SIZE:			Taille en pixel d'un carre pour representer une texture
**						/!\ pas encore proportionel a la taille fenetre ...
**	CUSTOM_MAP_NAME:	Nom du fichier lors d'une save.
**	MAP_CREA_MAX_MAP:	Nombre de map maximum & Utile aussi pour l'increment
**						du chiffre dans le nom du fichier.
*/
# define MC_TITLE "MAP CREATOR"
# define MC_INFO "Draw your map"
# define MC_SAVE "save"
# define TEXT 11
# define TEXT_P 16
# define CUSTOM_MAP_NAME "./custom_map_0.txt"
# define MAP_CREA_MAX_MAP '9' + 1
# define ITEM_SIZE 48

/*
**	Couleur
*/
# define CLR 0x00000000
# define WHITE 0xffffff
# define MAP_OVERLAY 0x2f1f1f1f
# define RED 0xff0000
# define GREEN 0x00ff00
# define BLUE 0x0000ff
# define BLUE_SKY 0x00bfff
# define DARK_RED 0xdf0000
# define DARK_GREY 0x1f1f1f
# define BROWN 0xcd661d
# define YELLOW 0xffff00
# define ORANGE 0xffa500
# define FOG CLR

/*
**	Event pour mlx_hook (voir X11.h)
*/
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define DESTROY_NOTIFY 17
# define KEY_PRESS_MASK (1L<<0)
# define KEY_RELEASE_MASK (1L<<1)
# define STRUCT_NOTIFY_MASK (1L<<17)

/*
**	GESTION DE LA TEXTURE DE POLICE DOOM
**
**	Nombre de caractere par ligne dans la texture
*/
# define NB_C 18

/*
**	Les caracteres sont dans des cases de 32 x 48 pixel.
**	Afin de ne pas copier les contour de la case, nous recuperons
**	un rectangle legerement plus petit definit ci dessous.
**	La premiere case commence au pixel 34 en x et 34 en y.
*/
# define FRAME_X 32
# define FRAME_Y 48
# define BOX_X FRAME_X - 2
# define BOX_Y FRAME_Y - 2
# define START_XY 34

/*
**	Le tableau de caractere correspond a l'ordre d'un tableau ascii.
**	Cela permet de retrouver a quel ligne et quel rang le caractere voulu
**	se situe. Il suffira ensuite de calculer les coordonnes en pixel reel.
*/
# define GET_Y(c) ((c - ' ') / NB_C)
# define GET_X(c) ((c - ' ') % NB_C)

/*
**	Calcul de la position reel du caractere en pixel.
*/
# define GET_POS_X(c) (START_XY + (FRAME_X * GET_X(c)) )
# define GET_POS_Y(c) (START_XY + (FRAME_Y * GET_Y(c)) )

/*
**	Caractere a gerer differement pour l'espacement
**	lors de l'affichage d'une chaine de caractere.
**	(Caracteres qui rentre dans une case de 16 x 48 pixel).
*/
# define TINY_CHAR ".,1l!':;]Iij|["

/*
**	Gestion des differents angle pour chaque mouvement,
**	une seule fonction pour le tout.
*/
# define RIGHT 90
# define LEFT -90
# define FORWARD 0
# define BEHIND 180

#endif
