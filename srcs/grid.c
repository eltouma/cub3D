/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 02:31:48 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/01 22:29:00 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	grid_line(t_img *img, t_map map, int tile_w)
{
	t_point	m;
	size_t	j;
	size_t	i;

	m.x = 0;
	j = 0;
	while (j <= map.rows)
	{
		m.y = j * tile_w;
		draw_h_line(img, m, map.cols * tile_w, 0xFF808080);
		j++;
	}
	m.y = 0;
	i = 0;
	while (i <= map.cols)
	{
		m.x = i * tile_w;
		draw_v_line(img, m, map.rows * tile_w, 0xFF808080);
		i++;
	}
}

void	grid(t_img *img, t_map map, int tile_w)
{
	t_point	m;
	size_t	i;
	size_t	j;

	j = 0;
	while (j < map.rows)
	{
		m.y = j * tile_w;
		i = 0;
		while (i < map.cols)
		{
			m.x = i * tile_w;
			if (map.tab[j][i] == '1')
				draw_tile(img, m, tile_w, 0xFFFFFFFF);
			else
				draw_tile(img, m, tile_w, 0x00000000);
			i++;
		}
		j++;
	}
	grid_line(img, map, tile_w);
}
