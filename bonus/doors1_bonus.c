/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 00:36:17 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/02 08:21:33 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

// Is a ray touching a door ?
int	ray_on_door(t_game game)
{
	if (rest(game.m.y, TS) > 0 && rest(game.m.x, TS) > 0)
		return (1);
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

// Give the status of a door from its j and i on the map
// Equivalent to get_door_idx
int	get_door_status(t_game game, int j, int i)
{
	int	k;

	k = 0;
	while (k < (game).nb_doors)
	{
		if ((game).doors[k].j == j && (game).doors[k].i == i)
		{
			(game).door_status = (game).doors[k].status;
			break ;
		}
		k++;
	}
	return ((game).door_status);
}

// Give the rest as double of a division by nbr
double	rest(double r, int nbr)
{
	int	k;

	if (nbr == 0)
		return (0);
	k = (int)(r / nbr);
	return (r - k * nbr);
}
