/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_inter_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 02:29:27 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/03 02:36:51 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
