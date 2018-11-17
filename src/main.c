/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 01:01:07 by banthony          #+#    #+#             */
/*   Updated: 2018/09/12 20:45:18 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		usage(char *bin)
{
	ft_putstr("Error: Usage ");
	ft_putstr(bin);
	ft_putendl(" [file.txt]\n\nGame control:");
	ft_putstr(KEY_1);
	ft_putstr(KEY_2);
	ft_putstr(KEY_3);
	ft_putendl("\nMap creator control:");
	ft_putstr(MC_USAGE);
	ft_putendl(MC_USAGE2);
	ft_putendl("To design a map you can use:");
	ft_putstr(HELP_1);
	ft_putstr(HELP_2);
	ft_putstr(HELP_3);
	ft_putendl("Spawn is optional.");
	ft_putendl("Minimum size map is 3 x 3 character.");
	ft_putendl("Maximum size map is 500 x 500 character.");
	ft_putstr("A map can contain only ");
	ft_putnbr(MAX_DOOR);
	ft_putendl(" doors.");
	ft_putstr("Door error notifications will be print only for the first ");
	ft_putnbr(MAX_DOOR);
	ft_putendl(" additional doors.");
	ft_exit(NULL, -1);
}

static void		wolf_run(t_wolf wolf)
{
	init(&wolf);
	mlx_mouse_hook(wolf.win, mousehook, &wolf);
	mlx_loop_hook(wolf.mlx, refresh, &wolf);
	mlx_hook(wolf.win, DESTROY_NOTIFY, STRUCT_NOTIFY_MASK, close_win, &wolf);
	mlx_hook(wolf.win, KEY_PRESS, KEY_PRESS_MASK, keypress, &wolf);
	mlx_hook(wolf.win, KEY_RELEASE, KEY_RELEASE_MASK, keyrelease, &wolf);
	mlx_loop(wolf.mlx);
}

/*
**	Les event clavier sont gere par mlx_hook sur un appui de touche
*/

int				main(int ac, char **av)
{
	char	*tmp;
	char	*line;
	int		fd;
	t_wolf	wolf;

	line = NULL;
	ft_bzero(&wolf, sizeof(wolf));
	if (ac != 2)
		usage(av[0]);
	if ((fd = open(av[1], O_RDONLY)) < 0)
		ft_exit(ERR_OPEN, -1);
	while ((get_next_line(fd, &line)) > 0)
	{
		tmp = ft_strtrim2(line);
		wolf.map = ft_tabadd(wolf.map, tmp);
		ft_strdel(&tmp);
		ft_strdel(&line);
	}
	if (!(map_is_valid(wolf.map, &wolf, 1)))
		wolf_exit(NULL, -1, &wolf);
	if (close(fd) < 0)
		wolf_exit(ERR_CLOSE, -1, &wolf);
	wolf_run(wolf);
	return (0);
}
