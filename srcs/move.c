/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:08:58 by eltouma           #+#    #+#             */
/*   Updated: 2024/10/01 22:38:22 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	move(t_game *game, int step_x, int step_y)
{
	t_point	p;

	p.x = (*game).map.pos_x + step_x;
	p.y = (*game).map.pos_y + step_y;
	if (is_wall((*game).map, p) == 0)
	{
		(*game).map.pos_x = p.x;
		(*game).map.pos_y = p.y;
		mlx_destroy_image((*game).mlx, (*game).cub.img);
		init_cub(game);
	}
}

void	move_dir(t_game *game, int step)
{
	t_point	p;
	double	rad;

	rad = (*game).map.alpha;
	p.x = (*game).map.pos_x + round(step * cos(rad));
	p.y = (*game).map.pos_y - round(step * sin(rad));
	if (is_wall((*game).map, p) == 0)
	{
		(*game).map.pos_x = p.x;
		(*game).map.pos_y = p.y;
		mlx_destroy_image((*game).mlx, (*game).cub.img);
		init_cub(game);
	}
}

void	move_dir2(t_game *game, int step)
{
	t_point	p;
	double	rad;

	rad = (*game).map.alpha + PI / 2;
	p.x = (*game).map.pos_x + round(step * cos(rad));
	p.y = (*game).map.pos_y - round(step * sin(rad));
	if (is_wall((*game).map, p) == 0)
	{
		(*game).map.pos_x = p.x;
		(*game).map.pos_y = p.y;
		mlx_destroy_image((*game).mlx, (*game).cub.img);
		init_cub(game);
	}
}

void	move_alpha(t_game *game, int deg)
{
	(*game).map.alpha = mod2pi((*game).map.alpha + deg * 2 * PI / 360);
	mlx_destroy_image((*game).mlx, (*game).cub.img);
	init_cub(game);
}
