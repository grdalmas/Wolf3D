/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator_drawing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 19:49:03 by banthony          #+#    #+#             */
/*   Updated: 2018/09/12 19:58:55 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**	Dessine les contours de la map avec la texture selectione.
*/

void	build_valid_map(t_wolf *w)
{
	char	texture;
	int		i;

	if (w->map_crea.texture == T_ERASER
		|| w->map_crea.texture == T_SPAWN)
		return ;
	texture = '0' + w->map_crea.texture;
	ft_memset(w->map_crea.map[0], texture,
				sizeof(char) * ft_strlen(w->map_crea.map[0]));
	i = w->map_crea.m_size.y - 1;
	ft_memset(w->map_crea.map[i], texture,
				sizeof(char) * ft_strlen(w->map_crea.map[i]));
	i = -1;
	while (++i < w->map_crea.m_size.y)
	{
		w->map_crea.map[i][0] = texture;
		w->map_crea.map[i][ft_strlen(w->map_crea.map[i]) - 1] = texture;
	}
}

/*
**	Maintenir la touche C pendant un clic dessine toute une colonne.
**	Maintenir la touche D pendant un clic dessine toute une ligne.
**	Fonctionne aussi avec la gomme, mais pas avec le spawn ou la porte.
*/

void	draw_on_map_crea(t_wolf *w, t_coord pt)
{
	char	texture;
	int		i;

	i = -1;
	if ((texture = '0' + w->map_crea.texture) == '0' + T_ERASER)
		texture = '0';
	if (w->keypress[KEY_C] && texture != '0' + T_SPAWN
							&& texture != '0' + T_DOOR)
	{
		while (++i < w->map_crea.m_size.y)
			w->map_crea.map[i][pt.x] = texture;
	}
	else if (w->keypress[KEY_D] && texture != '0' + T_SPAWN
								&& texture != '0' + T_DOOR)
		ft_memset(w->map_crea.map[pt.y], texture,
					sizeof(char) * ft_strlen(w->map_crea.map[pt.y]));
	else
		w->map_crea.map[pt.y][pt.x] = texture;
}
