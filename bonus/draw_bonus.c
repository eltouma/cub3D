/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 02:31:48 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/03 01:23:04 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

// Draw an horizontale line from the point P to P + length
// step = 1 pixel
void	draw_h_line(t_img *img, t_point p, int lenght, int color)
{
	int	i;

	i = 0;
	while (i < lenght)
	{
		put_pixel_img(img, (int)p.x + i, (int)p.y, color);
		i++;
	}
}

// From a point, go down (j increases), drawing pixel by pixel, till lenght
void	draw_v_line(t_img *img, t_point p, int lenght, int color)
{
	int	j;

	j = 0;
	while (j < lenght)
	{
		put_pixel_img(img, (int)p.x, (int)p.y + j, color);
		j++;
	}
}

void	draw_tile(t_img *img, t_point p, int lenght, int color)
{
	int		j;
	t_point	m;

	j = 0;
	m.x = p.x;
	while (j < lenght)
	{
		m.y = p.y + j;
		draw_h_line(img, m, lenght, color);
		j++;
	}
}

void	draw_angle_line(t_img *img, t_point p, double rad, double r)
{
	t_point	m;

	m.x = (int)p.x + (int)(r * cos(rad));
	m.y = (int)p.y - (int)(r * sin(rad));
	if (m.x <= (*img).img_w && m.y <= (*img).img_w && m.x >= 0 && m.y >= 0)
		draw_line(img, p, m, 0x0000FF00);
}

// From a point, go down (j increases), drawing pixel by pixel, till lenght
void	draw_s_line(t_img *img, t_point p, int lenght, int color)
{
	int		j;
	t_point	s;

	if ((int)p.x % TS != 0)
		draw_v_line(img, p, lenght, color);
	else
	{
		j = 0;
		while (j < lenght)
		{
			put_pixel_img(img, (int)p.x, (int)p.y + j, color);
			if (rand_range(0, 99999) == 6)
			{
				s.x = (int)p.x;
				s.y = (int)p.y + j;
				draw_point(img, s, 0x00FFFFFF);
			}
			j++;
		}
	}
}
