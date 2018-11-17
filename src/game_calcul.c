/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_calcul.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 16:16:59 by banthony          #+#    #+#             */
/*   Updated: 2018/09/08 20:01:08 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int				check_collision(t_vector pt, t_wolf *w, int hitbox_radius)
{
	t_coord		new_map;
	t_vector	new_pt;
	t_door		*door;
	int			i;

	i = -1;
	while (++i < 360)
	{
		new_pt.x = pt.x + (w->cos_table[i] * hitbox_radius);
		new_pt.y = pt.y + (w->sin_table[i] * hitbox_radius);
		new_map.x = (int)(new_pt.x / BLOC_SIZE);
		new_map.y = (int)(new_pt.y / BLOC_SIZE);
		if (new_map.x >= w->map_size.x || new_map.y >= w->map_size.y
		|| new_map.x < 0 || new_map.y < 0)
			return (1);
		if (w->map[new_map.y][new_map.x] > '0'
			&& w->map[new_map.y][new_map.x] < ('0' + ALL_WALL)
			&& w->map[new_map.y][new_map.x] != '0' + T_DOOR)
			return (1);
		if (w->map[new_map.y][new_map.x] == '0' + T_DOOR
			&& (door = get_door(w, pt)))
			if (door->timer < 1)
				return (1);
	}
	return (0);
}

void			move(t_wolf *w, int dir)
{
	t_vector	pt;
	double		move_x;
	double		move_y;

	move_x = d_cos(w->cam.pos.angle + dir) * w->cam.spd_move * w->time.delta;
	move_y = d_sin(w->cam.pos.angle + dir) * w->cam.spd_move * w->time.delta;
	pt = w->cam.pos;
	pt.x -= move_x;
	if (!(check_collision(pt, w, PLAYER_RADIUS)))
		w->cam.pos.x -= move_x;
	else
		pt = w->cam.pos;
	pt.y -= move_y;
	if (!(check_collision(pt, w, PLAYER_RADIUS)))
		w->cam.pos.y -= move_y;
}

unsigned int	fog(t_hit_info hit, unsigned int pixel,
								unsigned int fog_color, double fog_max)
{
	double			fog_rate;
	unsigned int	r;
	unsigned int	v;
	unsigned int	b;

	fog_rate = hit.real_dist / (fog_max - FOG_MIN);
	if (fog_rate < 0)
		fog_rate = 0;
	else if (fog_rate > 1)
		fog_rate = 1;
	r = (unsigned int)((1 - fog_rate) * ((pixel & RED) >> 16)
							+ fog_rate * ((fog_color & RED) >> 16));
	v = (unsigned int)((1 - fog_rate) * ((pixel & GREEN) >> 8)
							+ fog_rate * ((fog_color & GREEN) >> 8));
	b = (unsigned int)((1 - fog_rate) * (pixel & BLUE)
							+ fog_rate * (fog_color & BLUE));
	return ((r << 16) | (v << 8) | b);
}

t_door			*get_door(t_wolf *w, t_vector hit_point)
{
	int		i;
	t_coord	map;
	void	*ptr_door;

	ptr_door = NULL;
	map.x = (int)(hit_point.x / BLOC_SIZE);
	map.y = (int)(hit_point.y / BLOC_SIZE);
	if (map.x < w->map_size.x && map.y < w->map_size.y
		&& w->map[map.y][map.x] == '0' + T_DOOR)
		ptr_door = &w->map[map.y][map.x];
	i = -1;
	while (++i < MAX_DOOR && ptr_door)
	{
		if (ptr_door == w->doors[i].ptr)
			return (&w->doors[i]);
	}
	return (NULL);
}
