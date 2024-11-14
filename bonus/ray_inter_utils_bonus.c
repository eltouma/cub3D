/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_inter_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 02:29:27 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/03 00:09:19 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

int	is_outside_map(t_map map, t_point m)
{
	if ((size_t)m.y / TS > map.rows - 1 || (size_t)(m.x / TS) > map.cols - 1
		|| m.y < 0 || m.x < 0)
		return (1);
	return (0);
}

void	check_dy_h(int dy, int count, double rad, double *r)
{
	if (dy == 0)
	{
		*r = *r + TS / sin(rad);
		if (count == 1)
			*r = 0;
	}
	else
		*r = dy / sin(rad);
}

void	check_dy_h2(int dy, double rad, double *r)
{
	if (dy == 0)
		*r = *r + TS / fabs(sin(rad));
	else
		*r = (TS - dy) / fabs(sin(rad));
}

void	check_dx_v(int dx, int count, double rad, double *r)
{
	if (dx == 0)
	{
		*r = *r - TS / cos(rad);
		if (count == 1)
			*r = 0;
	}
	else
		*r = -dx / cos(rad);
}

void	check_dx_v2(int dx, double rad, double *r)
{
	if (dx == 0)
		*r = *r + TS / cos(rad);
	else
		*r = (TS - dx) / cos(rad);
}
