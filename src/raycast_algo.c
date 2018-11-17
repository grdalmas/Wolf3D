/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_algo1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 14:47:42 by banthony          #+#    #+#             */
/*   Updated: 2018/09/12 19:56:39 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int			door_vertical_handling(t_wolf *w, t_vector a, t_coord map,
											t_door *door)
{
	if (w->map[map.y - 1][map.x] && w->map[map.y + 1][map.x]
		&& w->map[map.y - 1][map.x] != '0' && w->map[map.y + 1][map.x] != '0'
		&& w->map[map.y - 1][map.x] != '0' + T_DOOR
		&& w->map[map.y + 1][map.x] != '0' + T_DOOR)
	{
		if (((int)a.y % BLOC_SIZE) == 0
			|| ((int)a.y % BLOC_SIZE) == BLOC_SIZE - 1)
			return (1);
		if ((fmod(a.y, BLOC_SIZE) / BLOC_SIZE) < door->timer)
			return (0);
		if (!(((int)a.x % BLOC_SIZE) < HALF_BLOC + 1
			&& ((int)a.x % BLOC_SIZE) > HALF_BLOC - 1))
			return (0);
	}
	return (1);
}

static int			door_handler(t_wolf *w, t_vector a, t_coord map)
{
	t_door	*door;

	if (w->map[map.y][map.x] == '0' + T_DOOR && (door = get_door(w, a)))
	{
		if (w->map[map.y][map.x + 1] && w->map[map.y][map.x - 1]
		&& w->map[map.y][map.x + 1] != '0' && w->map[map.y][map.x - 1] != '0'
		&& w->map[map.y][map.x + 1] != '0' + T_DOOR
		&& w->map[map.y][map.x - 1] != '0' + T_DOOR)
		{
			if (((int)a.x % BLOC_SIZE) == 0
				|| ((int)a.x % BLOC_SIZE) == BLOC_SIZE - 1)
				return (1);
			if ((fmod(a.x, BLOC_SIZE) / BLOC_SIZE) < door->timer)
				return (0);
			if (!(((int)a.y % BLOC_SIZE) < HALF_BLOC + 1
				&& ((int)a.y % BLOC_SIZE) > HALF_BLOC - 1))
				return (0);
		}
		return (door_vertical_handling(w, a, map, door));
	}
	return (1);
}

/*
**	Calcul du point correspondant dans la map
**	Si le point est bien dans la map
**	Et qu'il touche un objet a afficher (murs, portes, etc)
**	On arrondit le point, pour pouvoir utiliser le modulo
**	On enregistre le point dans hit_point
**	On return la texture a afficher
*/

static t_texture	find_intersection(t_wolf *w, t_vector a,
										t_hit_info *hit)
{
	t_coord		map;

	map.x = (int)(a.x / BLOC_SIZE);
	map.y = (int)(a.y / BLOC_SIZE);
	if (map.x < w->map_size.x && map.y < w->map_size.y)
	{
		if (w->map[map.y][map.x] > '0'
			&& w->map[map.y][map.x] < '0' + ALL_WALL)
		{
			if (door_handler(w, a, map))
			{
				my_round(&a);
				hit->point = a;
				hit->side = a.y;
				return ((t_texture)(w->map[map.y][map.x] - '0'));
			}
		}
	}
	return (0);
}

/*
**	Algo de trace de ligne DDA
**	Pour chaque point on verifie si il y a intersection avec un objet
**	dans la map. Si une intersection est trouve on stop le tracage.
*/

static t_texture	raycast(t_wolf *w, t_vector a, t_vector b,
										t_hit_info *hit)
{
	double		delta;
	int			i;
	t_vector	step;
	t_texture	texture;

	delta = fabs(b.y - a.y);
	if (fabs(b.x - a.x) >= delta)
		delta = fabs(b.x - a.x);
	step.x = (double)((b.x - a.x) / (double)delta);
	step.y = (double)((b.y - a.y) / (double)delta);
	i = -1;
	while (++i < delta)
	{
		if ((texture = find_intersection(w, a, hit)))
		{
			if (i % 2)
				hit->side = a.x;
			return (texture);
		}
		if (i % 2)
			a.x += step.x;
		else
			a.y += step.y;
	}
	return (0);
}

/*
**	Pour chaque colonne de pixel de l'ecran:
**	Calcul du point d'arrive du rayon (end)
**	Lancer du rayon via la fonction raycast
**	Recuperation des infos recu, dans la structure hit_info
**	Calcul de la distance reelle et projete du rayon, real_dist & dist
**	Calcul de la hauteur du mur en fonction de cette distance, (h_wall)
**	Enregistrement de quel axe a ete touche, x ou y (side)
**	Enregistrement de la texture a afficher
*/

void				launch_raycast(t_wolf *w)
{
	t_vector	end;
	t_texture	text;
	int			i;

	i = -1;
	while (++i < WIN_W)
	{
		end.x = (w->cam.pos.x - (w->cam.length_view *
				d_cos(w->cam.pos.angle + w->cam.ray_dir[i])));
		end.y = (w->cam.pos.y - (w->cam.length_view *
				d_sin(w->cam.pos.angle + w->cam.ray_dir[i])));
		if ((text = raycast(w, w->cam.pos, end, &w->hit[i])))
		{
			w->hit[i].real_dist = sqrt(((w->hit[i].point.y - w->cam.pos.y)
									* (w->hit[i].point.y - w->cam.pos.y))
									+ ((w->hit[i].point.x - w->cam.pos.x)
									* (w->hit[i].point.x - w->cam.pos.x)));
			w->hit[i].dist = d_cos(w->cam.ray_dir[i]) * w->hit[i].real_dist;
			w->hit[i].hwall = (BLOC_SIZE / w->hit[i].dist) * w->cam.screen_dist;
			w->hit[i].object = w->texture[text];
			w->hit[i].texture = text;
			if (w->hit[i].dist > w->max_dist)
				w->max_dist = w->hit[i].dist;
		}
	}
}
