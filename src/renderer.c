/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 17:01:58 by grdalmas          #+#    #+#             */
/*   Updated: 2018/09/04 19:25:54 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void			trace_floor_and_sky(t_img *img, t_coord start,
										double height_view, double half_wall)
{
	while (start.y >= 0)
	{
		put_pixel_img(start, BLUE_SKY, img);
		start.y--;
	}
	start.y = (int)(height_view + half_wall) - 2;
	while (start.y < img->size.y)
	{
		put_pixel_img(start, DARK_GREY, img);
		start.y++;
	}
}

static void			trace_textured_wall(t_wolf *w, t_coord pt, int h_wall,
											t_hit_info h)
{
	int			i;
	t_coord		ptt;
	t_door		*door;

	i = -1;
	ptt.x = (int)(h.object.size.x * (fmod(h.side, BLOC_SIZE) / BLOC_SIZE));
	if (h.texture == T_DOOR && (((int)h.point.x % BLOC_SIZE) == 0
			|| ((int)h.point.x % BLOC_SIZE) == BLOC_SIZE - 1))
		h.texture = T_DOOR_SIDE;
	else if (h.texture == T_DOOR && (((int)h.point.y % BLOC_SIZE) == 0
			|| ((int)h.point.y % BLOC_SIZE) == BLOC_SIZE - 1))
		h.texture = T_DOOR_SIDE;
	else if (h.texture == T_DOOR && (door = get_door(w, h.point)))
		ptt.x -= door->timer * h.object.size.x;
	while (++i < h_wall)
	{
		if (pt.y >= 0 && pt.y <= w->img[GAME].size.y)
		{
			ptt.y = h.object.size.y * i / h_wall;
			put_pixel_from_txt(pt, ptt, &w->texture[h.texture], &w->img[GAME]);
		}
		pt.y++;
	}
}

/*
**	(y % BLOC_SIZE) == 0 :	Face NORD ou SUD (hit sur ligne horizontale)
**	Si le joueur est en dessous du hit point, alors : Face NORD sinon SUD
**	(x % BLOC_SIZE) == 0 :	Face EST ou OUEST (hit sur ligne verticale)
**	Si le joueur est a gauche du hit point alors : Face OUEST sinon EST
*/

static void			find_orientation(t_wolf *w, t_coord pt,
											t_hit_info h, double fog_max)
{
	if (((int)h.point.y % BLOC_SIZE) == 0 && ((int)h.point.x % BLOC_SIZE) == 0)
		put_pixel_img(pt, fog(h, WHITE, FOG, fog_max), &w->img[GAME]);
	else if (((int)h.point.y % BLOC_SIZE) == 0)
	{
		if (w->cam.pos.y < h.point.y)
			put_pixel_img(pt, fog(h, RED, FOG, fog_max), &w->img[GAME]);
		else
			put_pixel_img(pt, fog(h, BLUE, FOG, fog_max), &w->img[GAME]);
	}
	else if (((int)h.point.x % BLOC_SIZE) == 0)
	{
		if (w->cam.pos.x < h.point.x)
			put_pixel_img(pt, fog(h, GREEN, FOG, fog_max), &w->img[GAME]);
		else
			put_pixel_img(pt, fog(h, YELLOW, FOG, fog_max), &w->img[GAME]);
	}
	else
		put_pixel_img(pt, fog(h, ORANGE, FOG, fog_max), &w->img[GAME]);
}

static void			trace_untextured_wall(t_wolf *w, t_coord pt,
											t_hit_info h, double fog_max)
{
	int i;
	int hwall;

	hwall = (int)h.hwall;
	i = -1;
	while (++i < hwall)
	{
		if (pt.y >= 0 && pt.y <= w->img[GAME].size.y)
			find_orientation(w, pt, h, fog_max);
		pt.y++;
	}
}

void				renderer(t_wolf *w)
{
	t_coord	start;
	double	half_wall;
	int		i;

	i = -1;
	while (++i < w->img[GAME].size.x)
	{
		half_wall = w->hit[i].hwall / 2;
		start.x = i;
		start.y = (int)(w->cam.height_view - half_wall);
		if (w->textured)
		{
			trace_textured_wall(w, start, (int)w->hit[i].hwall, w->hit[i]);
			trace_floor_and_sky(&w->img[GAME], start,
								w->cam.height_view, half_wall);
		}
		else
			trace_untextured_wall(w, start, w->hit[i], w->max_dist);
	}
}
