/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 19:11:32 by banthony          #+#    #+#             */
/*   Updated: 2018/09/08 17:43:54 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**	Necessaire pour usiliser cos, car la fonction de la libMath
**	utilise des radians.
*/

static double	to_radian(double degree)
{
	return (M_PI / 180 * degree);
}

double			d_cos(double degree)
{
	return (cos(to_radian(degree)));
}

double			d_sin(double degree)
{
	return (sin(to_radian(degree)));
}

double			d_tan(double degree)
{
	return (tan(to_radian(degree)));
}

void			my_round(t_vector *a)
{
	if ((int)(fmod(a->x, BLOC_SIZE)) == (int)(fmod(a->y, BLOC_SIZE)))
	{
		if (((int)(fmod(a->x, BLOC_SIZE)) == BLOC_SIZE - 1))
		{
			a->y = (int)(a->y + 1);
			a->x = (int)(a->x + 1);
		}
	}
	else if (fmod(a->x, BLOC_SIZE) < fmod(a->y, BLOC_SIZE))
		a->y = (int)(a->y + 1);
	else
		a->x = (int)(a->x + 1);
}
