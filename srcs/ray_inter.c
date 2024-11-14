/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 02:29:27 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/03 02:13:44 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// 0 <= rad <= PI, sin(rad) >= 0
// p.x = i * TS + dx
// p.y = j * TS + dy
double	ray_inter_h(t_map map, t_point p, double rad, t_point *m)
{
	int		dy;
	double	r;
	int		count;

	if (sin(rad) <= 0)
		return (WIN_W * WIN_W);
	*m = p;
	r = 0;
	count = 1;
	while (1)
	{
		dy = (int)(*m).y % TS;
		check_dy_h(dy, count, rad, &r);
		(*m).x = p.x + r * cos(rad);
		(*m).y = ((int)p.y - (int)p.y % TS) - count * TS;
		count++;
		if (is_outside_map(map, *m) == 1)
			return (r);
		if (map.tab[(int)(*m).y / TS][(int)((*m).x / TS)] == '1')
			return (r);
	}
}

// -PI < rad < 0, sin(rad) < 0
// p.x = i * TS + dx
// p.y = j * TS + dy
double	ray_inter_h2(t_map map, t_point p, double rad, t_point *m)
{
	int		dy;
	double	r;
	int		count;

	if (sin(rad) >= 0)
		return (WIN_W * WIN_W);
	*m = p;
	r = 0;
	count = 1;
	while (1)
	{
		dy = (int)(*m).y % TS;
		if (dy == 0)
			r = r + TS / fabs(sin(rad));
		else
			r = (TS - dy) / fabs(sin(rad));
		(*m).x = p.x + r * cos(rad);
		(*m).y = ((int)p.y - (int)p.y % TS) + count * TS;
		count++;
		if (is_outside_map(map, *m) == 1)
			return (r);
		if (map.tab[(int)(*m).y / TS][(int)((*m).x / TS)] == '1')
			return (r);
	}
}

// PI/2 < rad < PI, cos(rad) < 0
// -PI < rad < -PI/2, cos(rad) < 0
// p.x = i * TS + dx
// p.y = j * TS + dy
double	ray_inter_v(t_map map, t_point p, double rad, t_point *m)
{
	int		dx;
	double	r;
	int		count;

	if (cos(rad) >= 0)
		return (WIN_H * WIN_H);
	*m = p;
	r = 0;
	count = 1;
	while (1)
	{
		dx = (int)(*m).x % TS;
		check_dx_v(dx, count, rad, &r);
		(*m).y = p.y - r * sin(rad);
		(*m).x = ((int)p.x - (int)p.x % TS) - count * TS;
		count++;
		if (is_outside_map(map, *m) == 1)
			return (r);
		if (map.tab[(int)((*m).y / TS)][(int)(*m).x / TS] == '1')
			return (r);
	}
}

// -PI/2 < rad < PI/2, cos(rad) > 0
// p.x = i * TS + dx
// p.y = j * TS + dy
double	ray_inter_v2(t_map map, t_point p, double rad, t_point *m)
{
	int		dx;
	double	r;
	int		count;

	if (cos(rad) <= 0)
		return (WIN_W * WIN_W);
	*m = p;
	r = 0;
	count = 1;
	while (1)
	{
		dx = (int)(*m).x % TS;
		if (dx == 0)
			r = r + TS / cos(rad);
		else
			r = (TS - dx) / cos(rad);
		(*m).y = p.y - r * sin(rad);
		(*m).x = ((int)p.x - (int)p.x % TS) + count * TS;
		count++;
		if (is_outside_map(map, *m) == 1)
			return (r);
		if (map.tab[(int)((*m).y / TS)][(int)(*m).x / TS] == '1')
			return (r);
	}
}

int	is_outside_map(t_map map, t_point m)
{
	if ((size_t)m.y / TS > map.rows - 1 || (size_t)(m.x / TS) > map.cols - 1
		|| m.y < 0 || m.x < 0)
		return (1);
	return (0);
}
