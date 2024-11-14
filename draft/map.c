/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:43:49 by caguillo          #+#    #+#             */
/*   Updated: 2024/08/22 20:58:25 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// int   is_map_valid(t_map map);

// Parsing stage: we have a map, only one, at the last
//
int	get_map(char *argv1, t_map *map)
{
	if (get_dim(argv1, map) == KO)
		return (KO);
	(*map).tab = create_map(argv1, map); // print_mat((*map).tab);
	if (!(*map).tab)
		return (KO);
	if (is_map_closed(*map) == 0)
		return (double_free((*map).tab), putstr_fd(EUMC, 2), KO);
	if (handle_player(*map) == KO)
		return (double_free((*map).tab), putstr_fd(EUPL, 2), KO);
	double_free((*map).tab);
	return (OK);
}

// // return number player
// //
// int	is_multi_players(char *str)
// {
// 	int	i;

// 	if (!str)
// 		return (0);
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
// 		{
// 		//	printf("str[i] %c\n", str[i]);
// 			return (i);
// 		}
// 		i += 1;
// 	}
// 	return (0);
// }

// 0 return 0
// 1 valid
// > 1 return 0
int	handle_player(t_map map)
{
	int	i;
	int	j;
	int	count;

	if (!map.tab)
		return (KO);
	i = 0;
	count = 0;
	while (map.tab[i])
	{
		j = 0;
		while (map.tab[i][j])
		{
			if (map.tab[i][j] == 'N' || map.tab[i][j] == 'S' || map.tab[i][j] == 'E'
				|| map.tab[i][j] == 'W')
				count++;
			j++;	
		}
		i++;
	}
	//printf("%d", count);
	if (count == 0 || count > 1)
		return (KO);
	return (OK);
}

// /*****to do ************/
// // check duplicat ot missing player
// int	is_map_valid(t_map map)
// {
// 	int	i;
// 	char	player;
// 	char	tmp_player;

// 	if (!map.tab)
// 		return (0);
// 	i = 0;
// 	player = 0;
// 	tmp_player = 0;
// 	while (map.tab[i])
// 	{
// 		tmp_player = is_multi_players(map.tab[i]);
// 		if (tmp_player && player)
// 		{

// 	//		printf("Dans la boucle player = %d\ttmp_player = %d\ti vaut : %d\n",
			//	player, tmp_player, i);
// 			return (0);
// 		}
// 		else
// 		{
// 			if (tmp_player)
// 				player = tmp_player;
// 			tmp_player = 0;
// 		//	printf("Dans le else player = %d\ttmp_player = %d\ti vaut : %d\n",
			//	player, tmp_player, i);

// 		}
// 		i += 1;
// 	}
// 	if (!tmp_player && !player)
// 	{
// 	//	printf("player = %d\ttmp_player = %d\ti vaut : %d\n", player,
			//tmp_player, i);
// 		return (0);
// 	}
// 	return (1);
// }
// /******************** */

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
		//		printf("map.tab[%d] %s\n", i, map.tab[i]);
		if (!is_line_closed(map.tab[i]))
			return (0);
		i++;
	}
	trans = transpose(map.tab, map.rows, map.cols); // print_mat(trans);
	if (!trans)
		return (0);
	i = 0;
	while (trans[i])
	{
		//		printf("trans[%d] %s\n", i, trans[i]);
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
