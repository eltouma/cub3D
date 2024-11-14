/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 02:31:48 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/01 22:33:35 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
