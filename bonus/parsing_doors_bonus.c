/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_doors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 04:24:45 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/02 16:34:53 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

int	check_doors(t_game *game)
{
	size_t	i;
	size_t	j;

	if (!(*game).map.tab)
		return (KO);
	j = 0;
	while (j < (*game).map.rows)
	{
		i = 0;
		while (i < (*game).map.cols)
		{
			if ((*game).map.tab[j][i] == 'D')
			{
				if (is_valid_door((*game).map, j, i) == 1)
					(*game).nb_doors++;
				else
					return (free_game(game), err_msg(EUDR), KO);
			}
			i++;
		}
		j++;
	}
	return (get_doors(game));
}

int	is_valid_door(t_map map, size_t j, size_t i)
{
	if (i + 1 == map.cols || i == 0 || j + 1 == map.rows || j == 0
		|| map.tab[j][i + 1] == ' ' || map.tab[j + 1][i] == ' ' || map.tab[j][i
		- 1] == ' ' || map.tab[j - 1][i] == ' ')
		return (0);
	if (map.tab[j][i + 1] == '1' && map.tab[j][i - 1] == '1')
	{
		if ((map.tab[j + 1][i] == '0' || map.tab[j + 1][i] == 'D') && (map.tab[j
				- 1][i] == '0' || map.tab[j - 1][i] == 'D'))
			return (1);
		return (0);
	}
	if (map.tab[j + 1][i] == '1' && map.tab[j - 1][i] == '1')
	{
		if ((map.tab[j][i + 1] == '0' || map.tab[j][i + 1] == 'D')
			&& (map.tab[j][i - 1] == '0' || map.tab[j][i - 1] == '0'))
			return (1);
		return (0);
	}
	return (0);
}

int	get_doors(t_game *game)
{
	if ((*game).nb_doors > 0)
	{
		(*game).doors = ft_calloc((*game).nb_doors, sizeof(t_door));
		if (!(*game).doors)
			return (perror("cub3D"), free_game(game), KO);
		fill_doors(game);
	}
	return (OK);
}

void	fill_doors(t_game *game)
{
	size_t	i;
	size_t	j;
	int		k;

	k = 0;
	j = 0;
	while (j < (*game).map.rows)
	{
		i = 0;
		while (i < (*game).map.cols)
		{
			if ((*game).map.tab[j][i] == 'D')
			{
				(*game).doors[k].i = i;
				(*game).doors[k].j = j;
				(*game).doors[k].status = 0;
				k++;
			}
			i++;
		}
		j++;
	}
}
