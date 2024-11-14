/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 02:31:48 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/03 01:20:34 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

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

void	get_player_tile(t_point p, int *i, int *j, int tile_w)
{
	*i = (int)p.x / tile_w;
	*j = (int)p.y / tile_w;
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

int	rand_range(int min, int max)
{
	return ((rand() % (max - min + 1)) + min);
}
