/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_inter_v_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 02:29:27 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/04 23:37:01 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

static void	door_case0_v(double *r, double rad, t_point *m)
{
	(*m).x = (*m).x - (TS / 2);
	(*m).y = (*m).y - (TS / 2) * (-tan(rad));
	*r = *r - (TS / 2) / cos(rad);
}

static void	door_case1_v(t_game *game, double *r, double rad, t_point *m)
{
	if (get_diff_ms((*game).t1, (*game).t_door) < TD)
		(*game).lag.y = TS - (double)(get_diff_ms((*game).t1, (*game).t_door)
				* TS) / TD;
	else
		(*game).lag.y = 0;
	(*m).x = (*m).x - (TS / 2);
	(*m).y = (*m).y - (TS / 2) * (-tan(rad));
	*r = *r - (TS / 2) / cos(rad);
}

static void	door_case3_v(t_game *game, double *r, double rad, t_point *m)
{
	if (get_diff_ms((*game).t1, (*game).t_door) < TD)
		(*game).lag.y = (double)(get_diff_ms((*game).t1, (*game).t_door) * TS)
			/ TD;
	else
		(*game).lag.y = 0;
	(*m).x = (*m).x - (TS / 2);
	(*m).y = (*m).y - (TS / 2) * (-tan(rad));
	*r = *r - (TS / 2) / cos(rad);
}

static int	is_door_case_v(t_game *game, double *r, double rad, t_point *m)
{
	if (get_door_status(*game, (int)((*m).y / TS), (int)(*m).x / TS) == 0)
	{
		door_case0_v(r, rad, m);
		return (1);
	}
	else if (get_door_status(*game, (int)((*m).y / TS), (int)(*m).x / TS) == 1)
	{
		if (rest((*m).y - (TS / 2) * (-tan(rad)), TS) < TS
			- (double)(get_diff_ms((*game).t1, (*game).t_door) * TS) / TD)
		{
			door_case1_v(game, r, rad, m);
			return (1);
		}
	}
	else if (get_door_status(*game, (int)((*m).y / TS), (int)(*m).x / TS) == 3)
	{
		if (rest((*m).y - (TS / 2) * (-tan(rad)),
				TS) < (double)(get_diff_ms((*game).t1, (*game).t_door) * TS)
			/ TD)
		{
			door_case3_v(game, r, rad, m);
			return (1);
		}
	}
	return (0);
}

// PI/2 < rad < PI, cos(rad) < 0
// -PI < rad < -PI/2, cos(rad) < 0
// p.x = i * TS + dx
// p.y = j * TS + dy
// dx = (int)(*m).x % TS
double	ray_inter_v(t_game *game, t_point p, double rad, t_point *m)
{
	double	r;
	int		count;

	if (cos(rad) >= 0)
		return (WIN_H * WIN_H);
	*m = p;
	r = 0;
	count = 1;
	while (1)
	{
		check_dx_v((int)(*m).x % TS, count, rad, &r);
		(*m).y = p.y - r * sin(rad);
		(*m).x = ((int)p.x - (int)p.x % TS) - count * TS;
		count++;
		if (is_outside_map((*game).map, *m) == 1)
			return (r);
		if ((*game).map.tab[(int)((*m).y / TS)][(int)(*m).x / TS] == '1')
			return (r);
		if ((*game).map.tab[(int)((*m).y / TS)][(int)(*m).x / TS] == 'D'
			&& is_side_door_v(rad, (*m).y) == 0 && get_door_status(*game,
				(int)((*m).y / TS), (int)(*m).x / TS) != 2)
			if (is_door_case_v(game, &r, rad, m) == 1)
				return (r);
	}
}
