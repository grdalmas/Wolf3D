/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:58:11 by banthony          #+#    #+#             */
/*   Updated: 2018/09/12 19:57:01 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			eventk_map_creator(int keyhook, void *wolf)
{
	t_wolf	*w;
	int		i;

	i = -1;
	if (!(w = (t_wolf*)wolf))
		return (0);
	if (keyhook == MLX_KEY_ESCAPE)
		w->current_page = MAIN_MENU;
	if (keyhook == MLX_KEY_DEL)
	{
		ft_putendl("Reset map");
		while (++i < w->map_crea.m_size.y)
			ft_memset(w->map_crea.map[i], '0',
						sizeof(char) * ft_strlen(w->map_crea.map[i]));
	}
	else if (keyhook == MLX_KEY_V)
		build_valid_map(w);
	return (0);
}

static int	palette_choice(t_wolf *w, int x, int y)
{
	int		i;
	t_coord	pt;

	i = -1;
	pt.y = PERCENTAGE(50, w->img[GAME_I].size.y);
	pt.x = (PERCENTAGE(40, w->img[GAME_I].size.x));
	pt.x -= ((TEXT / 2) * ((ITEM_SIZE + 2) + TEXT_P));
	y -= w->img[MAP_CREATOR].size.y;
	while (++i < TEXT)
	{
		if (x > pt.x && x < (pt.x + ITEM_SIZE)
			&& y > pt.y && y < (pt.y + ITEM_SIZE))
			w->map_crea.texture = (t_texture)((int)T_STONE + i);
		pt.x += ITEM_SIZE + 2 + TEXT_P;
	}
	if (x > pt.x && x < (pt.x + ITEM_SIZE)
		&& y > pt.y && y < (pt.y + ITEM_SIZE))
		w->map_crea.texture = (t_texture)((int)T_ERASER);
	pt.x = PERCENTAGE(80, w->img[GAME_I].size.x);
	if (x > pt.x && x < (pt.x + (int)(ft_strlen(MC_SAVE) * 32))
		&& y > pt.y && y < (pt.y + ITEM_SIZE))
		save_map_into_file(w);
	return (0);
}

int			eventm_map_creator(int button, int x, int y, void *wolf)
{
	t_wolf	*w;
	t_coord pt;
	t_coord start;
	t_coord rest;

	if (!(w = (t_wolf*)wolf) && button >= 0)
		return (0);
	if (y > w->img[MAP_CREATOR].size.y)
		return (palette_choice(w, x, y));
	rest.x = (w->img[MAP_I].size.x % ITEM_SIZE) / 2;
	rest.y = (w->img[MAP_I].size.y % ITEM_SIZE) / 2;
	start.x = ((MAP_CRT_W - MAPI_W) / 2) + rest.x;
	start.y = ((MAP_CRT_H - MAPI_H) / 2) + rest.y;
	if (x < start.x || y < start.y || x > (start.x + MAPI_W - rest.x * 2)
		|| y > (start.y + MAPI_H - rest.y * 2))
		return (0);
	pt.x = (((x - start.x) / ITEM_SIZE));
	pt.y = (((y - start.y) / ITEM_SIZE));
	if (pt.y >= 0 && pt.y < w->map_crea.m_size.y
		&& pt.x >= 0 && pt.x < w->map_crea.m_size.x)
		draw_on_map_crea(w, pt);
	return (0);
}

static void	put_interface_text(t_wolf *w)
{
	t_coord pt;

	pt.x = PERCENTAGE(50, w->img[MAP_CREATOR].size.x);
	pt.y = PERCENTAGE(2, w->img[MAP_CREATOR].size.y);
	string_to_img(MC_TITLE, centerx_str(MC_TITLE, pt), &w->img[MAP_CREATOR], w);
	pt.x = PERCENTAGE(50, w->img[GAME_I].size.x);
	pt.y = PERCENTAGE(5, w->img[GAME_I].size.y);
	string_to_img(MC_INFO, centerx_str(MC_INFO, pt), &w->img[GAME_I], w);
}

void		draw_map_creator(void *wolf)
{
	t_wolf	*w;
	t_coord pt;

	if (!(w = (t_wolf*)wolf))
		return ;
	put_texture_on_img(&w->img[MAP_CREATOR], &w->texture[T_MAP_CREATOR]);
	put_texture_on_img(&w->img[GAME_I], &w->texture[T_CREATOR_INTERFACE]);
	mlx_put_image_to_window(w->mlx, w->win, w->img[w->current_page].ptr, 0, 0);
	mlx_put_image_to_window(w->mlx, w->win, w->img[GAME_I].ptr, 0,
							w->img[MAP_CREATOR].size.y);
	put_interface_text(w);
	draw_palette(w);
	pt.x = (PERCENTAGE(80, w->img[GAME_I].size.x));
	pt.y = PERCENTAGE(50, w->img[GAME_I].size.y);
	draw_text_button(MC_SAVE, w, GAME_I, pt);
	draw_grid(w, MAP_I, ITEM_SIZE);
	draw_map(w, w->map_crea.map, w->map_crea.m_size);
}
