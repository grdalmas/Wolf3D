/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 20:00:50 by banthony          #+#    #+#             */
/*   Updated: 2018/09/12 20:30:06 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**	Recuperation des compteurs puis increments.
**	Recuperation des 8 premiers bits avec le masque 0xFF.
**	Recuperation des 8 derniers bits avec le decalage de 8 bits vers la droite.
*/

static void		check_empty(char **map, t_coord i, short *map_err)
{
	short empty_bloc;
	short nb_door;

	empty_bloc = (short)(*map_err >> 8);
	nb_door = *map_err & 0xFF;
	if ((map[i.y][i.x] == '0' || map[i.y][i.x] == '0' + T_SPAWN) && !empty_bloc)
		empty_bloc = 1;
	if (map[i.y][i.x] == '0' + T_DOOR && nb_door < MAX_DOOR * 2)
	{
		nb_door++;
		if (nb_door >= MAX_DOOR)
		{
			ft_putstr(ERR_DOOR);
			ft_putstr("\tDoor num: ");
			ft_putnbr(nb_door);
			ft_putstr(" at: ");
			ft_putnbr(i.y);
			ft_putstr(" x ");
			ft_putnbr(i.x);
			ft_putendl(" coordinate.");
		}
	}
	*map_err = (short)((((short)empty_bloc) << 8) | nb_door);
}

/*
**	Cette fonction verifie que les blocs adjacent d'une porte sont:
**	Deux blocs vide en ligne et Deux murs en ligne.
**	Le premier if correspond a deux murs en ligne vertical (y).
**	Le deuxieme corresspond a deux murs en ligne horizontal (x).
*/

static int		check_adjacent_to_door(char **map, t_coord i)
{
	if (map[i.y][i.x] == '0' + T_DOOR)
	{
		if ((ft_strchr(WALL, map[i.y - 1][i.x])
		&& ft_strchr(WALL, map[i.y + 1][i.x]))
		&& ft_strchr(EMPTY_BLOC, map[i.y][i.x - 1])
		&& ft_strchr(EMPTY_BLOC, map[i.y][i.x + 1]))
			;
		else if ((ft_strchr(WALL, map[i.y][i.x - 1])
		&& ft_strchr(WALL, map[i.y][i.x + 1]))
		&& ft_strchr(EMPTY_BLOC, map[i.y - 1][i.x])
		&& ft_strchr(EMPTY_BLOC, map[i.y + 1][i.x]))
			;
		else
		{
			ft_putstr(ERR_DOOR_PLACEMENT);
			ft_putnbr(i.y);
			ft_putstr(" x ");
			ft_putnbr(i.x);
			ft_putendl(" coordinate.");
			return (1);
		}
	}
	return (0);
}

/*
**	Pour respecter la norme le compteur de portes et le compteur de bloc vide
**	sont fusionner dans la meme variable: map_err.
**	map_err est un short, donc sur 16bit.
**	Les bits de 0 a 7 sont reserve au compteur de portes.
**	Les bits de 8 a 15 sont reserve au compteur de bloc vide.
**	Le masque binaire 0x00FF recupere la valeur du compteur de portes.
**	Le masque binaire 0xFF00 recupere la valeur du compteur de bloc vide.
*/

static int		map_is_incoherent(char **map)
{
	t_coord i;
	short	map_err;
	int		door_err;

	map_err = 0;
	door_err = 0;
	i.y = -1;
	while (map[++i.y])
	{
		i.x = -1;
		while (map[i.y][++i.x])
		{
			check_empty(map, i, &map_err);
			door_err |= check_adjacent_to_door(map, i);
		}
	}
	if ((map_err & 0xFF00) == 0 || (map_err & 0x00FF) >= MAX_DOOR || door_err)
	{
		ft_putendl(ERR_MAP);
		return (1);
	}
	ft_printtab(map, ft_putstr, "\n");
	ft_putstr("\nMap OK!\n");
	return (0);
}

static size_t	line_is_valid(char *line, size_t y, size_t sizetab, int *spawn)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (!ft_strchr(WALL, line[0])
		|| !ft_strchr(WALL, (int)line[ft_strlen(line) - 1]))
		return (0);
	while (line[i])
	{
		if ((y == 0 || y == sizetab) && !ft_strchr(WALL, line[i]))
			return (0);
		if (line[i] == '0' + T_SPAWN)
			*spawn += 1;
		if (ft_isdigit((int)line[i]))
			len++;
		else if (line[i] != '0' + T_SPAWN)
			return (0);
		i++;
	}
	if (*spawn > 1)
		return (0);
	return (len);
}

size_t			map_is_valid(char **map, t_wolf *wolf, int save_size)
{
	int		i;
	size_t	len;
	size_t	tmp;
	int		spawn;

	spawn = 0;
	if ((len = ft_tablen(map)) > MAP_MAX || len < MAP_MIN)
		wolf_exit(ERR_MAP, -1, wolf);
	i = -1;
	if (save_size)
		wolf->map_size.y = (int)len;
	while (++i < (int)len)
	{
		if (!(tmp = line_is_valid(map[i], (size_t)i, len - 1, &spawn))
			|| tmp < MAP_MIN || tmp > MAP_MAX)
		{
			ft_putendl(ERR_MAP);
			return (0);
		}
		if ((int)tmp > wolf->map_size.x && save_size)
			wolf->map_size.x = (int)tmp;
	}
	if (map_is_incoherent(map))
		return (0);
	return (len);
}
