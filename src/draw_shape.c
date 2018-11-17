/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 19:13:48 by banthony          #+#    #+#             */
/*   Updated: 2018/09/05 17:04:33 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_palette(t_wolf *w)
{
	t_coord	pt;
	t_coord	box;
	t_coord	item_size;
	int		i;

	i = -1;
	item_size.x = ITEM_SIZE;
	item_size.y = ITEM_SIZE;
	box.x = item_size.x + 2;
	box.y = item_size.y + 2;
	pt.y = PERCENTAGE(50, w->img[GAME_I].size.y);
	pt.x = (PERCENTAGE(40, w->img[GAME_I].size.x));
	pt.x -= ((TEXT / 2) * (box.x + TEXT_P));
	while (++i < TEXT)
	{
		box.color = 0xd4af37;
		if (w->map_crea.texture == i + 1)
			box.color = 0xff0000;
		draw_box(box, pt, -1, &w->img[GAME_I]);
		put_texture_on_img_at(&w->img[GAME_I], &w->texture[T_STONE + i],
								pt, item_size);
		pt.x += box.x + TEXT_P;
	}
}

void	draw_box(t_coord size, t_coord start, int offset, t_img *img)
{
	t_coord i;
	t_coord max;

	start.x += offset;
	start.y += offset;
	i.x = start.x;
	i.y = start.y;
	max.x = start.x + size.x;
	max.y = start.y + size.y;
	while (i.y < max.y)
	{
		i.x = start.x;
		while (i.x < max.x)
		{
			if (i.x == start.x || i.y == start.y
				|| i.x == max.x - 1 || i.y == max.y - 1)
				put_pixel_img(i, size.color, img);
			i.x++;
		}
		i.y++;
	}
}

void	draw_text_button(char *str, t_wolf *w, t_page page, t_coord pt)
{
	t_coord box;

	box.x = (int)(ft_strlen(str) * 32);
	box.y = ITEM_SIZE + 2;
	box.color = 0xd4af37;
	draw_box(box, pt, 0, &w->img[page]);
	pt.x += (box.x / 2) + 7;
	pt.y += 3;
	string_to_img(str, centerx_str(str, pt), &w->img[page], w);
}

/*
**	Affiche la map en utilisant les textures.
**	Une echelle de dessin (taille des carre) est cacule
**	en fonction de la taille de l'img et de la map,
**	via la fonction map_scaler()
**
**	Fonction de 27 lignes:
**	Faire une fonction pour l'affichage du joueur dans la map.
*/

void	draw_map(t_wolf *w, char **map, t_coord map_size)
{
	t_coord		p;
	t_coord		i;
	t_coord		rest;
	t_texture	text;
	t_coord		it;

	if (!w || !map)
		return ;
	it.x = (int)(round(ITEM_SIZE / map_scaler(map_size, w->img[MAP_I].size)));
	it.y = it.x;
	rest.x = (w->img[MAP_I].size.x - (it.x * map_size.x)) / 2;
	rest.y = (w->img[MAP_I].size.y - (it.y * map_size.y)) / 2;
	i.y = -1;
	while (map[++i.y])
	{
		i.x = -1;
		p.y = (i.y * it.y) + rest.y;
		while (map[i.y][++i.x])
		{
			p.x = (i.x * it.x) + rest.x;
			if ((text = (t_texture)(map[i.y][i.x] - '0')))
				put_texture_on_img_at(&w->img[MAP_I], &w->texture[text], p, it);
		}
	}
}

void	draw_grid(t_wolf *w, t_page page, int square)
{
	t_coord pt;
	t_coord	box;
	t_coord rest;

	box.x = square;
	box.y = square;
	box.color = 0x2f2f2f;
	rest.x = (w->img[page].size.x % box.x) / 2;
	rest.y = (w->img[page].size.y % box.y) / 2;
	pt.x = rest.x;
	pt.y = rest.y;
	while (pt.y < w->img[page].size.y - rest.y)
	{
		pt.x = rest.x;
		while (pt.x < w->img[page].size.x - rest.x)
		{
			draw_box(box, pt, 0, &w->img[page]);
			pt.x += box.x;
		}
		pt.y += box.y;
	}
}
