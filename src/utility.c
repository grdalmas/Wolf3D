/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 18:57:47 by banthony          #+#    #+#             */
/*   Updated: 2018/09/08 20:02:56 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		save_map_into_file(t_wolf *w)
{
	char	*tmp;
	char	*path;
	char	c;
	int		fd;

	c = '0' - 1;
	if (!(map_is_valid(w->map_crea.map, w, 0)))
		return ;
	path = ft_strdup(CUSTOM_MAP_NAME);
	while ((fd = open(path, O_CREAT | O_WRONLY | O_EXCL, 0700)) < 0
				&& ++c < MAP_CREA_MAX_MAP)
	{
		if ((tmp = ft_strrchr(path, '_')) && ft_strlen(tmp) > 1)
			ft_strncpy(tmp + 1, &c, 1);
	}
	ft_putendl(path);
	ft_strdel(&path);
	if (fd < 0)
	{
		perror(strerror(errno));
		return ;
	}
	c = -1;
	while ((int)++c < w->map_crea.m_size.y)
		ft_putendl_fd(w->map_crea.map[(int)c], fd);
}

void		wolf_exit(char *str, int status, t_wolf *wolf)
{
	if (wolf)
	{
		ft_freetab(wolf->map);
		ft_freetab(wolf->map_crea.map);
	}
	ft_exit(str, status);
}

/*
**	Charge dans une structure img, un fichier xpm.
*/

static int	load_img(char *path, t_img *i, t_wolf *wolf)
{
	i->endian = 0;
	i->ptr = mlx_xpm_file_to_image(wolf->mlx, path, &i->size.x, &i->size.y);
	if (!i->ptr)
	{
		ft_putstr("Texture ");
		ft_putstr(path);
		ft_putstr(" : NOT LOADED !!\n");
		return (1);
	}
	i->data = mlx_get_data_addr(i->ptr, &i->bpp, &i->width, &i->endian);
	i->octet = (unsigned int)(i->bpp / 8);
	ft_putstr("Texture ");
	ft_putstr(path);
	ft_putstr(" : LOADED - size in px: ");
	ft_putnbr(i->size.x);
	ft_putstr(" x ");
	ft_putnbrendl(i->size.y);
	return (0);
}

/*
**	A revoir, si le nombre de texture augmente:
**	Creer un tableau statique dans un header contenant tout les path
**	Boucler sur ce tableau pour charger les texture
**	Arreter a la moindre erreur
*/

int			load_texture(t_wolf *w)
{
	int error;

	error = 0;
	error |= load_img("./texture/doom_font.xpm", &w->texture[T_FONT], w);
	error |= load_img("./texture/main_menu.xpm", &w->texture[T_MAIN_MENU], w);
	error |= load_img("./texture/interface_creator.xpm",
						&w->texture[T_CREATOR_INTERFACE], w);
	error |= load_img("./texture/map_creator.xpm",
						&w->texture[T_MAP_CREATOR], w);
	error |= load_img("./texture/eraser_icon.xpm", &w->texture[T_ERASER], w);
	error |= load_img("./texture/greystone.xpm", &w->texture[T_STONE], w);
	error |= load_img("./texture/wood.xpm", &w->texture[T_WOOD], w);
	error |= load_img("./texture/redbrick.xpm", &w->texture[T_REDBRICK], w);
	error |= load_img("./texture/door.xpm", &w->texture[T_DOOR], w);
	error |= load_img("./texture/purplestone.xpm",
						&w->texture[T_PURPLESTONE], w);
	error |= load_img("./texture/eagle.xpm", &w->texture[T_EAGLE], w);
	error |= load_img("./texture/mossy.xpm", &w->texture[T_MOSSY], w);
	error |= load_img("./texture/bluestone.xpm", &w->texture[T_BLUESTONE], w);
	error |= load_img("./texture/colorstone.xpm", &w->texture[T_COLORSTONE], w);
	error |= load_img("./texture/door_side.xpm", &w->texture[T_DOOR_SIDE], w);
	error |= load_img("./texture/spawn_cross.xpm", &w->texture[T_SPAWN], w);
	if (error)
		return (0);
	return (1);
}

double		map_scaler(t_coord map_size, t_coord img_size)
{
	t_vector	scale;
	double		final_scale;

	if (map_size.x == (img_size.x / ITEM_SIZE))
		return (1.0);
	if (map_size.y == (img_size.y / ITEM_SIZE))
		return (1.0);
	scale.x = ((double)((map_size.x + 1) * ITEM_SIZE) / (double)img_size.x);
	scale.y = ((double)((map_size.y + 1) * ITEM_SIZE) / (double)img_size.y);
	if (scale.x > scale.y)
		final_scale = scale.x;
	else
		final_scale = scale.y;
	if (final_scale > ITEM_SIZE)
		final_scale = ITEM_SIZE;
	if (final_scale < 0.5)
		return (1.0);
	return (final_scale);
}
