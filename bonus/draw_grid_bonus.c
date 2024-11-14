/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 01:16:14 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/03 01:34:43 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

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

void	grid_line_mini(t_img *img, t_map map, int tile_w)
{
	t_point	m;
	int		j;
	int		i;

	m.x = 0;
	j = 0;
	while (j <= min(SIZE_MINI, map.rows))
	{
		m.y = j * tile_w;
		draw_h_line(img, m, min(SIZE_MINI, map.cols) * tile_w, 0xFF808080);
		j++;
	}
	m.y = 0;
	i = 0;
	while (i <= min(SIZE_MINI, map.cols))
	{
		m.x = i * tile_w;
		draw_v_line(img, m, min(SIZE_MINI, map.rows) * tile_w, 0xFF808080);
		i++;
	}
}

void	grid_mini(t_img *img, t_map *map, int tile_w, t_point p)
{
	t_point	m;
	int		i;
	int		j;

	get_mini_limit(map, tile_w, p);
	j = 0;
	while (j < min(SIZE_MINI, (int)(*map).rows) && (*map).j_mini
		+ j < (int)(*map).rows && (*map).j_mini + j >= 0)
	{
		m.y = j * tile_w;
		i = 0;
		while (i < min(SIZE_MINI, (int)(*map).cols) && (*map).i_mini
			+ i < (int)(*map).cols && (*map).i_mini + i >= 0)
		{
			m.x = i * tile_w;
			if ((*map).tab[(*map).j_mini + j][(*map).i_mini + i] == '1')
				draw_tile(img, m, tile_w, 0xFFFFFFFF);
			else if ((*map).tab[(*map).j_mini + j][(*map).i_mini + i] == 'D')
				draw_tile(img, m, tile_w, 0xFF808080);
			else
				draw_tile(img, m, tile_w, 0x00000000);
			i++;
		}
		j++;
	}
}
// grid_line_mini(img, *map, tile_w);

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
			else if (map.tab[j][i] == 'D')
				draw_tile(img, m, tile_w, 0xFF808080);
			else
				draw_tile(img, m, tile_w, 0x00000000);
			i++;
		}
		j++;
	}
	grid_line(img, map, tile_w);
}

void	get_mini_limit(t_map *map, int tile_w, t_point p)
{
	int	p_i;
	int	p_j;

	get_player_tile(p, &p_i, &p_j, tile_w);
	while ((*map).i_mini >= p_i)
		(*map).i_mini--;
	while (p_i + 1 >= (*map).i_mini + SIZE_MINI)
		(*map).i_mini++;
	while ((*map).j_mini >= p_j)
		(*map).j_mini--;
	while (p_j + 1 >= (*map).j_mini + SIZE_MINI)
		(*map).j_mini++;
}
