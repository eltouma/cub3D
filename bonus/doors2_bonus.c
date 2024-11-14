/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 00:36:17 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/02 16:30:16 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

void	move_door(t_game *game)
{
	if (is_front_door(game) == 1)
	{
		if ((*game).doors[(*game).door_idx].status == 0)
		{
			clock_gettime(CLOCK_MONOTONIC, &(*game).t_door);
			(*game).doors[(*game).door_idx].status = 1;
		}
		else if ((*game).doors[(*game).door_idx].status == 2)
		{
			clock_gettime(CLOCK_MONOTONIC, &(*game).t_door);
			(*game).doors[(*game).door_idx].status = 3;
		}
	}
}
// printf("front door %d\n", (*game).door_idx);
// printf("NO front door\n");
// printf("door closed\n");
// printf("door opened\n");

int	is_front_door(t_game *game)
{
	t_point	p;

	p.x = (*game).map.pos_x / TS;
	p.y = (*game).map.pos_y / TS;
	if (PI / 4 <= (*game).map.alpha && (*game).map.alpha <= 3 * PI / 4)
	{
		if ((*game).map.tab[(int)(p.y) - 1][(int)(p.x)] == 'D')
			return (get_door_idx(game, (int)(p.y) - 1, (int)(p.x)), 1);
	}
	else if (-PI / 4 <= (*game).map.alpha && (*game).map.alpha <= PI / 4)
	{
		if ((*game).map.tab[(int)(p.y)][(int)(p.x) + 1] == 'D')
			return (get_door_idx(game, (int)(p.y), (int)(p.x) + 1), 1);
	}
	else if (-3 * PI / 4 <= (*game).map.alpha && (*game).map.alpha <= -PI / 4)
	{
		if ((*game).map.tab[(int)(p.y) + 1][(int)(p.x)] == 'D')
			return (get_door_idx(game, (int)(p.y) + 1, (int)(p.x)), 1);
	}
	else
	{
		if ((*game).map.tab[(int)(p.y)][(int)(p.x) - 1] == 'D')
			return (get_door_idx(game, (int)(p.y), (int)(p.x) - 1), 1);
	}
	return (0);
}

int	is_door_closed(t_game game, t_point p)
{
	if (game.map.tab[(size_t)p.y / TS][(size_t)p.x / TS] == 'D')
	{
		if (get_door_status(game, (size_t)p.y / TS, (size_t)p.x / TS) != 2)
			return (1);
	}
	return (0);
}
