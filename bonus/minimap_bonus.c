/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 21:26:57 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/03 01:30:50 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

void	minimap(t_game *game)
{
	t_point	p;
	t_point	m;

	p.x = (*game).map.pos_x;
	p.y = (*game).map.pos_y;
	if ((*game).mini_maxi % 2 == 0)
	{
		grid_mini(&(*game).cub, &(*game).map, TS, p);
		grid_line_mini(&(*game).cub, (*game).map, TS);
		m.x = p.x - (*game).map.i_mini * TS;
		m.y = p.y - (*game).map.j_mini * TS;
		draw_point(&(*game).cub, m, 0x00FF0000);
	}
	else
		maximap(game);
}
// put_pixel_img(&(*game).cub, 20, 20, 0x00000000);
// put_pixel_img(&(*game).cub, 22, 20, 0x00000000);
// put_pixel_img(&(*game).cub, 20, 22, 0x00000000);
// put_pixel_img(&(*game).cub, 22, 22, 0x00000000);

void	maximap(t_game *game)
{
	t_point	p;
	double	rad;
	double	r;
	int		i;

	p.x = (*game).map.pos_x;
	p.y = (*game).map.pos_y;
	grid(&(*game).cub, (*game).map, TS);
	i = -(*game).cub.img_w / 2;
	while (i < (*game).cub.img_w / 2)
	{
		rad = mod2pi((*game).map.alpha - atan(i / (*game).d_proj));
		r = ray(game, p, rad);
		draw_angle_line(&(*game).cub, p, rad, r);
		i++;
	}
}
