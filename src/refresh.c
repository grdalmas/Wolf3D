/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 23:33:23 by banthony          #+#    #+#             */
/*   Updated: 2018/09/12 19:49:13 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			new_img(t_wolf *w, t_page page, t_coord size)
{
	ft_memset((void*)&w->img[page], 0, sizeof(t_img));
	w->img[page].size = size;
	w->img[page].ptr = mlx_new_image(w->mlx, size.x, size.y);
	if (!w->img[page].ptr)
		wolf_exit(ERR_IMG, -1, w);
	w->img[page].width = size.x;
	w->img[page].data = mlx_get_data_addr(w->img[page].ptr, &w->img[page].bpp,
									&w->img[page].width, &w->img[page].endian);
	w->img[page].octet = (unsigned int)(w->img[page].bpp / 8);
	return (1);
}

static void	img_clear(t_wolf *w, t_page page)
{
	t_coord size;

	size = w->img[page].size;
	mlx_destroy_image(w->mlx, w->img[page].ptr);
	new_img(w, page, size);
}

int			refresh(void *wptr)
{
	t_wolf	*wolf;

	wolf = NULL;
	if (!(wolf = (t_wolf*)wptr))
		return (0);
	wolf->time.update(&wolf->time);
	wolf->time.print(&wolf->time);
	img_clear(wolf, wolf->current_page);
	if (wolf->current_page == MAP_CREATOR)
	{
		img_clear(wolf, MAP_I);
		img_clear(wolf, GAME_I);
	}
	if (wolf->current_page == GAME)
		img_clear(wolf, MAP_I);
	expose((t_wolf*)wptr);
	return (1);
}

/*
**	Les pages GAME et MAP_CREATOR ont besoin respectivement de la gestion
**	de la map et map + interface.
**
**	Event:
**	La fonction d'event_key est appele dans l'expose, les statuts des touches
**	sont memorise dans keypress / keyrelease.
**	Cette methode resout le probleme de latence entre l'appui sur une touche
**	et l'action bind sur la touche.
**	Le champ LAST_KEY_PRESS est remis a zero, et nous permet
**	d'avoir une alternative au keyrepeat qui est tres rapide.
*/

void		expose(t_wolf *w)
{
	if (w->cam.pos.angle < 0 || w->cam.pos.angle > 360)
		w->cam.pos.angle = fmod(fmod(w->cam.pos.angle, 360) + 360, 360);
	w->event_key[w->current_page](w->keypress[LAST_KEY_PRESS], w);
	w->keypress[LAST_KEY_PRESS] = 0;
	w->draw[w->current_page](w);
	mlx_put_image_to_window(w->mlx, w->win, w->img[w->current_page].ptr, 0, 0);
	if (w->current_page == GAME)
	{
		if (w->keypress[KEY_TAB])
		{
			fill_img(&w->img[MAP_I], MAP_OVERLAY);
			draw_map(w, w->map, w->map_size);
			mlx_put_image_to_window(w->mlx, w->win, w->img[MAP_I].ptr
									, w->mini_map.x, w->mini_map.y);
		}
	}
	else if (w->current_page == MAP_CREATOR)
	{
		mlx_put_image_to_window(w->mlx, w->win, w->img[MAP_I].ptr,
							w->map_crea.grid_pos.x, w->map_crea.grid_pos.y);
		mlx_put_image_to_window(w->mlx, w->win, w->img[GAME_I].ptr, 0,
							w->img[MAP_CREATOR].size.y);
	}
}
