/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 02:31:48 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/03 01:37:02 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// Put a pixel in the image on (x,y)
// bpp = 32
// (*img).line_lgh = 1920
// x * des bytes
// dst = (*img).addr + (y * (*img).line_lgh + x * ((*img).bpp / 8));
void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > (*img).img_w - 1 || y > (*img).img_h - 1)
		return ;
	dst = (*img).addr + (y * (*img).line_lgh + x * sizeof(int));
	*(unsigned int *)dst = color;
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

void	draw_point(t_img *img, t_point p, int color)
{
	put_pixel_img(img, (int)p.x, (int)p.y, color);
	put_pixel_img(img, (int)p.x + 1, (int)p.y, color);
	put_pixel_img(img, (int)p.x - 1, (int)p.y, color);
	put_pixel_img(img, (int)p.x + 2, (int)p.y, color);
	put_pixel_img(img, (int)p.x - 2, (int)p.y, color);
	put_pixel_img(img, (int)p.x, (int)p.y + 1, color);
	put_pixel_img(img, (int)p.x, (int)p.y - 1, color);
	put_pixel_img(img, (int)p.x, (int)p.y + 2, color);
	put_pixel_img(img, (int)p.x, (int)p.y - 2, color);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
