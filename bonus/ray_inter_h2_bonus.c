/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_inter_h2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 02:29:27 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/04 23:37:10 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

static void	door_case0_h2(double *r, double rad, t_point *m)
{
	(*m).x = (*m).x - (TS / 2) / tan(rad);
	(*m).y = (*m).y + (TS / 2);
	*r = *r - (TS / 2) / sin(rad);
}

static void	door_case1_h2(t_game *game, double *r, double rad, t_point *m)
{
	if (get_diff_ms((*game).t1, (*game).t_door) < TD)
		(*game).lag.x = (double)(get_diff_ms((*game).t1, (*game).t_door) * TS)
			/ TD;
	else
		(*game).lag.x = 0;
	(*m).x = (*m).x - (TS / 2) / tan(rad);
	(*m).y = (*m).y + (TS / 2);
	*r = *r - (TS / 2) / sin(rad);
}

static void	door_case3_h2(t_game *game, double *r, double rad, t_point *m)
{
	if (get_diff_ms((*game).t1, (*game).t_door) < TD)
		(*game).lag.x = TS - (double)(get_diff_ms((*game).t1, (*game).t_door)
				* TS) / TD;
	else
		(*game).lag.x = 0;
	*r = *r - (TS / 2) / sin(rad);
	(*m).x = (*m).x - (TS / 2) / tan(rad);
	(*m).y = (*m).y + (TS / 2);
}

static int	is_door_case_h2(t_game *game, double *r, double rad, t_point *m)
{
	if (get_door_status(*game, (int)(*m).y / TS, (int)((*m).x / TS)) == 0)
	{
		door_case0_h2(r, rad, m);
		return (1);
	}
	else if (get_door_status(*game, (int)(*m).y / TS, (int)((*m).x / TS)) == 1)
	{
		if (rest((*m).x - (TS / 2) / tan(rad),
				TS) > (double)(get_diff_ms((*game).t1, (*game).t_door) * TS)
			/ TD)
		{
			door_case1_h2(game, r, rad, m);
			return (1);
		}
	}
	else if (get_door_status(*game, (int)(*m).y / TS, (int)((*m).x / TS)) == 3)
	{
		if (rest((*m).x - (TS / 2) / tan(rad), TS) > TS
			- (double)(get_diff_ms((*game).t1, (*game).t_door) * TS) / TD)
		{
			door_case3_h2(game, r, rad, m);
			return (1);
		}
	}
	return (0);
}

// -PI < rad < 0, sin(rad) < 0
// p.x = i * TS + dx
// p.y = j * TS + dy
// dy = (int)(*m).y % TS
double	ray_inter_h2(t_game *game, t_point p, double rad, t_point *m)
{
	double	r;
	int		count;

	if (sin(rad) >= 0)
		return (WIN_W * WIN_W);
	*m = p;
	r = 0;
	count = 1;
	while (1)
	{
		check_dy_h2((int)(*m).y % TS, rad, &r);
		(*m).x = p.x + r * cos(rad);
		(*m).y = ((int)p.y - (int)p.y % TS) + count * TS;
		count++;
		if (is_outside_map((*game).map, *m) == 1)
			return (r);
		if ((*game).map.tab[(int)(*m).y / TS][(int)((*m).x / TS)] == '1')
			return (r);
		if ((*game).map.tab[(int)(*m).y / TS][(int)((*m).x / TS)] == 'D'
			&& is_side_door_h2(rad, (*m).x) == 0 && get_door_status(*game,
				(int)(*m).y / TS, (int)((*m).x / TS)) != 2)
			if (is_door_case_h2(game, &r, rad, m) == 1)
				return (r);
	}
}
