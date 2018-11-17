/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 17:17:38 by banthony          #+#    #+#             */
/*   Updated: 2018/09/05 18:05:32 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int				mousehook(int button, int x, int y, t_wolf *wolf)
{
	if (!wolf)
		return (0);
	wolf->event_mouse[wolf->current_page](button, x, y, wolf);
	return (0);
}

int				keypress(int keycode, void *w)
{
	t_wolf *wolf;

	if (!(wolf = (t_wolf*)w))
		return (0);
	if (keycode == MLX_KEY_TAB)
		wolf->keypress[KEY_TAB] = 1;
	else if (keycode == MLX_KEY_W)
		wolf->keypress[KEY_W] = 1;
	else if (keycode == MLX_KEY_D)
		wolf->keypress[KEY_D] = 1;
	else if (keycode == MLX_KEY_LEFT)
		wolf->keypress[KEY_LEFT] = 1;
	else if (keycode == MLX_KEY_A)
		wolf->keypress[KEY_A] = 1;
	else if (keycode == MLX_KEY_S)
		wolf->keypress[KEY_S] = 1;
	else if (keycode == MLX_KEY_RIGHT)
		wolf->keypress[KEY_RIGHT] = 1;
	else if (keycode == MLX_KEY_C)
		wolf->keypress[KEY_C] = 1;
	else if (keycode == MLX_KEY_SHIFT_LEFT)
		wolf->keypress[KEY_SHIFT] = 1;
	wolf->keypress[LAST_KEY_PRESS] = keycode;
	return (1);
}

int				keyrelease(int keycode, void *w)
{
	t_wolf *wolf;

	if (!(wolf = (t_wolf*)w))
		return (0);
	if (keycode == MLX_KEY_TAB)
		wolf->keypress[KEY_TAB] = 0;
	else if (keycode == MLX_KEY_W)
		wolf->keypress[KEY_W] = 0;
	else if (keycode == MLX_KEY_D)
		wolf->keypress[KEY_D] = 0;
	else if (keycode == MLX_KEY_LEFT)
		wolf->keypress[KEY_LEFT] = 0;
	else if (keycode == MLX_KEY_A)
		wolf->keypress[KEY_A] = 0;
	else if (keycode == MLX_KEY_S)
		wolf->keypress[KEY_S] = 0;
	else if (keycode == MLX_KEY_RIGHT)
		wolf->keypress[KEY_RIGHT] = 0;
	else if (keycode == MLX_KEY_C)
		wolf->keypress[KEY_C] = 0;
	else if (keycode == MLX_KEY_SHIFT_LEFT)
		wolf->keypress[KEY_SHIFT] = 0;
	return (1);
}

int				close_win(void *wolf)
{
	t_wolf *w;

	if (!(w = (t_wolf *)wolf))
		return (0);
	wolf_exit("fermeture croix", 0, w);
	return (0);
}
