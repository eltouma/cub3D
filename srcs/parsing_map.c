/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:43:49 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/03 02:32:10 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// Parsing stage: we have a map, only one, at the last of the scene
int	get_map(char *argv1, t_map *map)
{
	if (get_dim(argv1, map) == KO)
		return (KO);
	(*map).tab = create_map(argv1, map);
	if (!(*map).tab)
		return (KO);
	if (is_map_closed(*map) == 0)
		return (double_free((*map).tab), err_msg(EUMC), KO);
	if (handle_player(map, 0) == KO)
		return (double_free((*map).tab), err_msg(EUPL), KO);
	return (OK);
}

// 0 return 0
// 1 valid
// > 1 return 0
int	handle_player(t_map *map, int count)
{
	int	i;
	int	j;

	if (!map->tab)
		return (KO);
	i = 0;
	while (map->tab[i])
	{
		j = 0;
		while (map->tab[i][j])
		{
			if (map->tab[i][j] == 'N' || map->tab[i][j] == 'S'
				|| map->tab[i][j] == 'E' || map->tab[i][j] == 'W')
			{
				count++;
				if (count == 1)
					update_player_map(map, map->tab[i][j], j, i);
			}
			j++;
		}
		i++;
	}
	if (count == 0 || count > 1)
		return (KO);
	return (OK);
}

void	update_player_map(t_map *map, char player, int pos_x, int pos_y)
{
	if (player == 'N')
		(*map).alpha = PI / 2;
	if (player == 'S')
		(*map).alpha = -PI / 2;
	if (player == 'E')
		(*map).alpha = 0;
	if (player == 'W')
		(*map).alpha = PI;
	(*map).pos_x = pos_x * TS + (int)(TS / 2);
	(*map).pos_y = pos_y * TS + (int)(TS / 2);
	(*map).tab[pos_y][pos_x] = '0';
	(*map).map_w = (*map).cols * TS;
	(*map).map_h = (*map).rows * TS;
}

// check if each line of the map is well closed
// and if each line of the transpose de map (so the columms of map)
// is well closed too
int	is_map_closed(t_map map)
{
	int		i;
	char	**trans;

	if (!map.tab)
		return (0);
	i = 0;
	while (map.tab[i])
	{
		if (!is_line_closed(map.tab[i]))
			return (0);
		i++;
	}
	trans = transpose(map.tab, map.rows, map.cols);
	if (!trans)
		return (0);
	i = 0;
	while (trans[i])
	{
		if (!is_line_closed(trans[i]))
			return (double_free(trans), 0);
		i++;
	}
	return (double_free(trans), 1);
}

int	is_line_closed(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '0' || str[i] == 'N' || str[i] == 'S' || str[i] == 'E'
			|| str[i] == 'W')
		{
			if (i == 0)
				return (0);
			if (i > 0 && is_space(str[i - 1]) == 1)
				return (0);
			if (str[i + 1] == '\0' || is_space(str[i + 1]) == 1)
				return (0);
		}
		i++;
	}
	return (1);
}
