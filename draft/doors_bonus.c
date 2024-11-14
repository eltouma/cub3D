/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 00:36:17 by caguillo          #+#    #+#             */
/*   Updated: 2024/09/26 01:26:35 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

// void	set_doors(t_map *map)
// {
// 	size_t	j;
// 	size_t	i;
// 	int		count;

// 	count = 0;
// 	j = 0;
// 	while (j < (*map).rows)
// 	{
// 		i = 0;
// 		while (i < (*map).cols)
// 		{
// 			if (is_door_place(*map, j, i) == 1 && count < NBR_DOORS)
// 			{
// 				(*map).tab[j][i] = 'D';
// 				count++;
// 				// printf("j = %ld, i = %ld\n", j, i);
// 				break ;
// 			}
// 			i++;
// 		}
// 		j++;
// 	}
// }

// int	is_door_place(t_map map, size_t j, size_t i)
// {
// 	if (map.tab[j][i] != '1')
// 		return (0);
// 	// if (map.tab[j][i] == '1' && (i + 1 == map.cols || i == 0))
// 	// 	return (0);
// 	// if (map.tab[j][i] == '1' && (j + 1 == map.rows || j == 0))
// 	// 	return (0);
// 	// if (map.tab[j][i] == '1' && map.tab[j][i + 1] == ' ')
// 	// 	return (0);
// 	// if (map.tab[j][i] == '1' && map.tab[j + 1][i] == ' ')
// 	// 	return (0);
// 	// if (map.tab[j][i] == '1' && map.tab[j][i - 1] == ' ')
// 	// 	return (0);
// 	// if (map.tab[j][i] == '1' && map.tab[j - 1][i] == ' ')
// 	// 	return (0);
// 	if (i + 1 == map.cols || i == 0 || j + 1 == map.rows || j == 0
// 		|| map.tab[j][i + 1] == ' ' || map.tab[j + 1][i] == ' ' || map.tab[j][i
// 		- 1] == ' ' || map.tab[j - 1][i] == ' ')
// 		return (0);
// 	if (map.tab[j][i + 1] == '1' && map.tab[j][i - 1] == '1')
// 	{
// 		if (map.tab[j + 1][i] == '0' && map.tab[j - 1][i] == '0')
// 			return (1);
// 		return (0);
// 	}
// 	if (map.tab[j + 1][i] == '1' && map.tab[j - 1][i] == '1')
// 	{
// 		if (map.tab[j][i + 1] == '0' && map.tab[j][i - 1] == '0')
// 			return (1);
// 		return (0);
// 	}
// 	return (0);
// }

int	is_door(t_game game)
{
	// printf("m.y %f, m.x %f\n", game.m.y, game.m.x);
	// printf("m.y %d, m.x %d\n", (int)(game.m.y / TILE_SIZE), (int)(game.m.x
	// 		/ TILE_SIZE));
	// printf("%c\n", game.map.tab[(int)(game.m.y / TILE_SIZE)][(int)(game.m.x
	// 		/ TILE_SIZE)]);
	// if (game.map.tab[(int)(game.m.y / TILE_SIZE)][(int)(game.m.x
	// 		/ TILE_SIZE)] == 'D')
	// 	return (1);
	// if ((int)game.m.y % TILE_SIZE != 0 && (int)game.m.x % TILE_SIZE != 0)
	// 	return (1);
	if (rest(game.m.y, TILE_SIZE) > 0 && rest(game.m.x, TILE_SIZE) > 0)
		return (1);
	// if (game.map.is_door == 1)
	// 	return (1);
	return (0);
}

// Give the index of a door from its j and i on the map
int	get_door_idx(t_game *game, int j, int i)
{
	int	k;

	k = 0;
	while (k < (*game).nb_doors)
	{
		if ((*game).doors[k].j == j && (*game).doors[k].i == i)
		{
			(*game).door_idx = k;
			break ;
		}
		k++;
	}
	return (k);
}

//
int	get_door_status(t_game *game, int j, int i)
{
	(*game).door_status = (*game).doors[get_door_idx(game, j, i)].status;
	return ((*game).door_status);
}

double	rest(double r, int nbr)
{
	int	k;

	if (nbr == 0)
		return (0);
	k = (int)(r / nbr);
	// printf("reste = %f", r - k * nbr);
	return (r - k * nbr);
}
