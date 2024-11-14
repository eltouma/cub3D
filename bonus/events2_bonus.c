/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:08:58 by eltouma           #+#    #+#             */
/*   Updated: 2024/10/02 16:31:19 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

void	move_dir2(t_game *game, int step)
{
	t_point	p;
	double	rad;

	rad = (*game).map.alpha + PI / 2;
	p.x = (*game).map.pos_x + round(step * cos(rad));
	p.y = (*game).map.pos_y - round(step * sin(rad));
	if (is_wall((*game).map, p) == 0)
	{
		if (is_corner((*game).map, p) == 0)
		{
			if (is_door_closed(*game, p) == 0)
			{
				(*game).map.pos_x = p.x;
				(*game).map.pos_y = p.y;
				mlx_destroy_image((*game).mlx, (*game).cub.img);
				init_cub(game);
			}
		}
	}
}

void	move_alpha(t_game *game, int deg)
{
	(*game).map.alpha = mod2pi((*game).map.alpha + deg * 2 * PI / 360);
	mlx_destroy_image((*game).mlx, (*game).cub.img);
	init_cub(game);
}

// return 1 in case of a wall
// return 1 also when outside the map.tab
// outside map.tab
// hit wall?
// to avoid to have head inside the wall (0 % 48)
int	is_wall(t_map map, t_point p)
{
	if (p.x < TS || p.y < TS)
		return (1);
	if ((size_t)p.y / TS > map.rows - 1)
		return (1);
	if ((size_t)p.x / TS > map.cols - 1)
		return (1);
	if (map.tab[(size_t)p.y / TS][(size_t)p.x / TS] == '1')
		return (1);
	if (map.tab[(size_t)((p.y - 1) / TS)][(size_t)p.x / TS] == '1')
		return (1);
	if (map.tab[(size_t)((p.y + 1) / TS)][(size_t)p.x / TS] == '1')
		return (1);
	if (map.tab[(size_t)(p.y) / TS][(size_t)((p.x - 1) / TS)] == '1')
		return (1);
	if (map.tab[(size_t)(p.y) / TS][(size_t)((p.x + 1) / TS)] == '1')
		return (1);
	if (map.tab[(size_t)((p.y + 1) / TS)][(size_t)((p.x + 1) / TS)] == '1')
		return (1);
	if (map.tab[(size_t)((p.y - 1) / TS)][(size_t)((p.x - 1) / TS)] == '1')
		return (1);
	if (map.tab[(size_t)((p.y - 1) / TS)][(size_t)((p.x + 1) / TS)] == '1')
		return (1);
	if (map.tab[(size_t)((p.y + 1) / TS)][(size_t)((p.x - 1) / TS)] == '1')
		return (1);
	return (0);
}
// if ((int)p.x % TS == 0 || (int)p.y % TS == 0)
//	return (1);
// printf("%ld %ld\n", (size_t)((p.y - 1) / TS), (size_t)p.x/ TS);
// printf("%ld %ld\n", (size_t)((p.y + 1) / TS), (size_t)p.x/ TS);
// printf("%ld %ld\n", (size_t)((p.y )/TS),(size_t)((p.x-1)/ TS));
// printf("%ld %ld\n", (size_t)((p.y )/TS),(size_t)((p.x+1)/ TS));
// printf("%ld %ld\n", (size_t)((p.y+1)/TS),(size_t)((p.x+1)/TS));
// printf("%ld %ld\n", (size_t)((p.y-1)/TS),(size_t)((p.x-1)/TS));
// printf("%ld %ld\n", (size_t)((p.y-1)/TS),(size_t)((p.x+1)/TS));
// printf("%ld %ld\n", (size_t)((p.y+1)/TS),(size_t)((p.x-1)/TS));

// Should be enough, as soon as out of range, put back inside the range
double	mod2pi(double rad)
{
	if (rad > PI)
		return (rad - 2 * PI);
	if (rad < -PI)
		return (rad + 2 * PI);
	return (rad);
}

int	is_corner(t_map map, t_point p)
{
	if (map.tab[(size_t)map.pos_y / TS][(size_t)p.x / TS] == '1'
		&& map.tab[(size_t)p.y / TS][(size_t)map.pos_x / TS] == '1')
		return (printf("corner\n"), 1);
	return (0);
}

// // Not in use so far
// void	move(t_game *game, int step_x, int step_y)
// {
// 	t_point	p;

// 	p.x = (*game).map.pos_x + step_x;
// 	p.y = (*game).map.pos_y + step_y;
// 	if (is_wall((*game).map, p) == 0)
// 	{
// 		(*game).map.pos_x = p.x;
// 		(*game).map.pos_y = p.y;
// 		mlx_destroy_image((*game).mlx, (*game).cub.img);
// 		init_cub(game);
// 	}
// 	// printf("pos x = %ld\n", (*game).map.pos_x);
// 	// printf("pos y = %ld\n", (*game).map.pos_y);
// }

// // general 2kpi
// double	mod2pi(double rad)
// {
// 	if (rad > PI)
// 		return (mod2pi(rad - 2 * PI));
// 	if (rad < -PI)
// 		return (mod2pi(rad + 2 * PI));
// 	return (rad);
// }
