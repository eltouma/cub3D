/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:08:58 by eltouma           #+#    #+#             */
/*   Updated: 2024/10/03 02:27:08 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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

// int	is_wall_2(t_map map, t_point p)
// {
// 	if (map.tab[(size_t)(p.y) / TS][(size_t)((p.x - 1) / TS)] == '1')
// 		return (1);
// 	if (map.tab[(size_t)(p.y) / TS][(size_t)((p.x + 1) / TS)] == '1')
// 		return (1);
// 	if (map.tab[(size_t)((p.y + 1) / TS)][(size_t)((p.x + 1) / TS)] == '1')
// 		return (1);
// 	if (map.tab[(size_t)((p.y - 1) / TS)][(size_t)((p.x - 1) / TS)] == '1')
// 		return (1);
// 	if (map.tab[(size_t)((p.y - 1) / TS)][(size_t)((p.x + 1) / TS)] == '1')
// 		return (1);
// 	if (map.tab[(size_t)((p.y + 1) / TS)][(size_t)((p.x - 1) / TS)] == '1')
// 		return (1);
// 	return (0);
// }

// // return 1 in case of a wall
// // return 1 also when outside the map.tab
// int	is_wall(t_map map, t_point p)
// {
// 	if (p.x < TS || p.y < TS)
// 		return (1);
// 	if ((size_t)p.y / TS > map.rows - 1)
// 		return (1);
// 	if ((size_t)p.x / TS > map.cols - 1)
// 		return (1);
// 	if (map.tab[(size_t)p.y / TS][(size_t)p.x / TS] == '1')
// 		return (1);
// 	if (map.tab[(size_t)((p.y - 1) / TS)][(size_t)p.x / TS] == '1')
// 		return (1);
// 	if (map.tab[(size_t)((p.y + 1) / TS)][(size_t)p.x / TS] == '1')
// 		return (1);
// 	is_wall_2(map, p);
// 	return (0);
// }
