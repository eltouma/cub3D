/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 02:31:48 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/03 01:23:58 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"


void	draw_line(t_img *img, t_point a, t_point b, int color)
{
	t_point	m;
	double	d;

	m = a;
	if (a.x < b.x && (fabs(b.y - a.y) <= fabs(b.x - a.x)))
	{
		d = (a.y - b.y) / (a.x - b.x);
		while (m.x != b.x)
		{
			put_pixel_img(img, (int)m.x, (int)m.y, color);
			m.x = m.x + 1 * (b.x - a.x) / fabs(b.x - a.x);
			m.y = d * m.x + (a.y - d * a.x);
		}
	}
	else if (a.x > b.x && (fabs(b.y - a.y) <= fabs(b.x - a.x)))
	{
		d = (a.y - b.y) / (a.x - b.x);
		while (m.x != b.x)
		{
			put_pixel_img(img, (int)m.x, (int)m.y, color);
			m.x = m.x + 1 * (b.x - a.x) / fabs(b.x - a.x);
			m.y = d * m.x + (a.y - d * a.x);
		}
	}
	else if (a.y > b.y && (fabs(b.y - a.y) >= fabs(b.x - a.x)))
	{
		d = (a.x - b.x) / (a.y - b.y);
		while (m.y != b.y)
		{
			put_pixel_img(img, (int)m.x, (int)m.y, color);
			m.y = m.y + 1 * (b.y - a.y) / fabs(b.y - a.y);
			m.x = d * (m.y - a.y) + a.x;
		}
	}
	else if (a.y < b.y && (fabs(b.y - a.y) >= fabs(b.x - a.x)))
	{
		d = (a.x - b.x) / (a.y - b.y);
		while (m.y != b.y)
		{
			put_pixel_img(img, (int)m.x, (int)m.y, color);
			m.y = m.y + 1 * (b.y - a.y) / fabs(b.y - a.y);
			m.x = d * (m.y - a.y) + a.x;
		}
	}
	// put_pixel_img(img, (int)a.x, (int)a.y, 0x0FF00000);
	// put_pixel_img(img, (int)b.x, (int)b.y, 0x0FF00000);
	draw_point(img, a, 0x00FF0000);
	draw_point(img, b, 0x00FF0000);
}

