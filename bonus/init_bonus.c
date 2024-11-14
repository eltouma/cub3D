/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 21:16:51 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/02 16:27:03 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

void	init(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	ft_memset(&game->data, 0, sizeof(t_data));
	ft_memset(&game->map, 0, sizeof(t_map));
	ft_memset(&game->cub, 0, sizeof(t_img));
	ft_memset(&game->m, 0, sizeof(t_point));
	(*game).sprite1 = NULL;
	(*game).sprite2 = NULL;
	(*game).doors = NULL;
}

int	check_input(int argc, char **argv)
{
	if (argc > 2)
		return (err_msg(ETMA), KO);
	if (argc < 2)
		return (err_msg(EMIS), KO);
	if (check_file_ext(argv[1], ".cub") == KO)
		return (err_msg(EEXT), KO);
	return (OK);
}

int	check_file_ext(char *fullname, char *ext)
{
	int	n;
	int	k;
	int	i;

	k = ft_strlen(ext);
	n = ft_strlen(fullname);
	if (n <= k)
		return (KO);
	i = 0;
	while (i < k)
	{
		if (fullname[n - i - 1] != ext[k - i - 1])
			return (KO);
		i++;
	}
	return (OK);
}

// Check if there is a NULL inside the tab
int	check_tab_xpm(t_game *game)
{
	int	i;

	i = 0;
	while (i < IMG_NBR)
	{
		if (!(*game).tab_img[i])
			return (KO);
		i++;
	}
	return (OK);
}
