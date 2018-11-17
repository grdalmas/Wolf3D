/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 13:54:12 by banthony          #+#    #+#             */
/*   Updated: 2018/08/04 22:02:43 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**	Le caractere '6' est manquant dans la texture doom_font.xpm
**	Nous devons donc utiliser le '9', auquel on applique une rotation de 180deg.
**	Il est necessaire d'appliquer une constante de repositionnement,
**	afin que le caractere soit centre dans un mot.
*/

static void	handle_six(t_coord pt, t_img *img, t_wolf *wolf)
{
	t_coord			i;
	t_coord			calc;
	t_coord			pt_t;
	int				constante;

	constante = 5;
	i.y = -1;
	while (++i.y < BOX_Y)
	{
		i.x = -1;
		while (++i.x < BOX_X - constante)
		{
			calc.x = ((-1 * i.x)) + (pt.x + (BOX_X - constante));
			calc.y = (-1 * (i.y - constante)) + (pt.y + (BOX_Y) / 2);
			pt_t.x = i.x + GET_POS_X('9' - 1);
			pt_t.y = i.y + GET_POS_Y('9' - 1);
			put_pixel_from_txt(calc, pt_t, &wolf->texture[T_FONT], img);
		}
	}
}

/*
**	Fonction qui gere les exception du tableau:
**	Le 'l' qui est dans une case de 16 x 48 pixel.
**	Le '6' qui est inexistant.
**	Le 'm' qui est dans une case de 48 x 48 pixel.
*/

static char	handle_exceptions(char c, t_coord *var, t_coord *pt_t)
{
	if (c == '6')
		return ('6');
	if (c > '6')
		var->y = 1;
	pt_t->x = GET_POS_X(c - var->y);
	pt_t->y = GET_POS_Y(c - var->y);
	if (c == 'l')
		var->x = 14;
	if (c == 'm')
	{
		var->x += 16;
		pt_t->x -= 16;
	}
	return (0);
}

/*
**	Copie la case correspondant au caractere c, depuis la texture vers l'image.
**	La copie est faite dans l'image a la position pt.
*/

static void	char_to_img(char c, t_coord pt, t_img *img, t_wolf *w)
{
	unsigned int	pos;
	unsigned int	text_pos;
	t_coord			pt_t;
	t_coord			var;

	var.y = 0;
	var.x = BOX_X;
	if (!c || c <= 32 || pt.x + BOX_X > WIN_W || pt.y + BOX_Y > WIN_H
		|| pt.x < 0 || pt.y < 0)
		return ;
	if ((handle_exceptions(c, &var, &pt_t)) == '6')
		handle_six(pt, img, w);
	var.y = -1;
	while (++var.y < BOX_Y && c != '6')
	{
		pos = (unsigned int)((var.y + pt.y) * img->width)
				+ ((unsigned int)pt.x * img->octet);
		text_pos = (unsigned int)((pt_t.y + var.y) * w->texture[T_FONT].width)
				+ ((unsigned int)pt_t.x * w->texture[T_FONT].octet);
		ft_memcpy(img->data + pos, w->texture[T_FONT].data
				+ text_pos, (size_t)((img->octet) * (unsigned int)(var.x)));
	}
}

/*
**	Affichage d'une chaine de caractere, et gestion de l'espacement
**	entre les caracteres, qui tiennent sur une case de 16 x 48 pixel.
*/

void		string_to_img(char *str, t_coord pt, t_img *img, t_wolf *wolf)
{
	int		i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
	{
		char_to_img(str[i], pt, img, wolf);
		if (ft_strchr(TINY_CHAR, str[i]))
			pt.x -= 15;
		pt.x += BOX_X;
	}
}

/*
** Securiser la fonction !
*/

t_coord		centerx_str(char *str, t_coord pt)
{
	size_t len;

	if (!str)
		return (pt);
	len = ft_strlen(str);
	if ((pt.x -= (len / 2) * 32) < 0)
		pt.x = 0;
	return (pt);
}
