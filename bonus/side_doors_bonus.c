/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_doors_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:38:46 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/05 22:08:25 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

// dx != 0 != TS
int	is_side_door_h(double rad, double mx)
{
	double	max;
	double	min;
	double	dx;

	dx = rest(mx, TS);
	max = PI - atan((TS / 2) / dx);
	min = atan((TS / 2) / (TS - dx));
	if (min < rad && rad < max)
		return (0);
	return (1);
}

int	is_side_door_h2(double rad, double mx)
{
	double	max;
	double	min;
	double	dx;

	dx = rest(mx, TS);
	max = atan((TS / 2) / (dx - TS));
	min = atan((TS / 2) / dx) - PI;
	if (min < rad && rad < max)
		return (0);
	return (1);
}

int	is_side_door_v(double rad, double my)
{
	double	max;
	double	min;
	double	dy;

	dy = rest(my, TS);
	max = -PI + atan((TS - dy) / (TS / 2));
	min = PI - atan(dy / (TS / 2));
	if ((min < rad && rad < PI) || (-PI < rad && rad < max))
		return (0);
	return (1);
}

int	is_side_door_v2(double rad, double my)
{
	double	max;
	double	min;
	double	dy;

	dy = rest(my, TS);
	max = atan(dy / (TS / 2));
	min = atan((dy - TS) / (TS / 2));
	if (min < rad && rad < max)
		return (0);
	return (1);
}

int	is_side_door(t_game game, double rad)
{
	if ((0 <= rad && rad <= PI) && (game).horv == 'h')
		if ((game).map.tab[(int)(game.m.y / TS) + 1][(int)(game.m.x
				/ TS)] == 'D')
			return (1);
	if ((-PI <= rad && rad <= 0) && (game).horv == 'h')
		if ((game).map.tab[(int)(game.m.y / TS) - 1][(int)(game.m.x
				/ TS)] == 'D')
			return (1);
	if ((-PI / 2 <= rad && rad <= PI / 2) && (game).horv == 'v')
		if ((game).map.tab[(int)(game.m.y / TS)][(int)(game.m.x / TS)
			- 1] == 'D')
			return (1);
	if ((PI / 2 <= rad && rad <= PI) && (game).horv == 'v')
		if ((game).map.tab[(int)(game.m.y / TS)][(int)(game.m.x / TS)
			+ 1] == 'D')
			return (1);
	if ((-PI <= rad && rad <= -PI / 2) && (game).horv == 'v')
		if ((game).map.tab[(int)(game.m.y / TS)][(int)(game.m.x / TS)
			+ 1] == 'D')
			return (1);
	return (0);
}
