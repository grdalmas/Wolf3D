/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:40:31 by banthony          #+#    #+#             */
/*   Updated: 2018/09/05 15:19:07 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			eventk_menu(int keyhook, void *wolf)
{
	t_wolf *w;

	if (!(w = (t_wolf*)wolf))
		return (0);
	if (keyhook == MLX_KEY_ESCAPE)
		wolf_exit("Escape menu", 0, w);
	else if (keyhook == MLX_KEY_UP && w->cursor > GAME)
		w->cursor--;
	else if (keyhook == MLX_KEY_DOWN && w->cursor < MAP_CREATOR + 1)
		w->cursor++;
	else if (keyhook == MLX_KEY_ENTER && w->cursor >= GAME
										&& w->cursor <= MAP_CREATOR)
		w->current_page = (t_page)w->cursor;
	else if (keyhook == MLX_KEY_ENTER)
		wolf_exit(QUIT, 0, w);
	return (0);
}

int			eventm_menu(int button, int x, int y, void *wolf)
{
	(void)wolf;
	(void)button;
	(void)x;
	(void)y;
	return (0);
}

/*
**	Remplacer MENU_ENTRY par un enum
*/

static void	print_menu(struct s_coord (*pt)[NB_MENU_ENTRY],
						char *(menu)[NB_MENU_ENTRY], t_wolf *w)
{
	int i;

	i = -1;
	(*pt)[TITLE].x = PERCENTAGE(50, w->img[MAIN_MENU].size.x);
	(*pt)[TITLE].y = PERCENTAGE(20, w->img[MAIN_MENU].size.y);
	(*pt)[RUN] = (*pt)[TITLE];
	(*pt)[MAP_CREA] = (*pt)[TITLE];
	(*pt)[EXIT] = (*pt)[TITLE];
	(*pt)[RUN].y += 240;
	(*pt)[MAP_CREA].y = (*pt)[RUN].y + 48;
	(*pt)[EXIT].y = (*pt)[MAP_CREA].y + 48;
	while (++i < NB_MENU_ENTRY)
		string_to_img(menu[i], centerx_str(menu[i], (*pt)[i]),
							&w->img[MAIN_MENU], w);
}

void		draw_main_menu(void *wolf)
{
	t_coord	pt[NB_MENU_ENTRY];
	char	*menu[NB_MENU_ENTRY];
	t_wolf	*w;

	if (!(w = (t_wolf*)wolf))
		return ;
	menu[TITLE] = G_NAME;
	menu[RUN] = G_RUN;
	menu[MAP_CREA] = G_MC;
	menu[EXIT] = G_EXIT;
	put_texture_on_img(&w->img[MAIN_MENU], &w->texture[T_MAIN_MENU]);
	mlx_put_image_to_window(w->mlx, w->win, w->img[w->current_page].ptr, 0, 0);
	print_menu(&pt, menu, w);
	if (w->cursor)
	{
		pt[w->cursor].x -= 32 * (1 + (ft_strlen(menu[w->cursor]) / 2));
		string_to_img(">", pt[w->cursor], &w->img[MAIN_MENU], w);
		pt[w->cursor].x += 32 * (1 + (ft_strlen(menu[w->cursor])));
		string_to_img("<", pt[w->cursor], &w->img[MAIN_MENU], w);
	}
}
