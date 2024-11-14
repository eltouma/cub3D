/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:20:12 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/01 23:27:44 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_data(t_data *data)
{
	free((*data).north);
	free((*data).south);
	free((*data).west);
	free((*data).east);
}

void	*free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		tab[i++] = NULL;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}

void	double_free(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_newtab(char **tab, int j)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (i < j)
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_cub(t_game *game)
{
	destroy_all_xpm(game);
	mlx_destroy_image((*game).mlx, (*game).cub.img);
	mlx_destroy_window((*game).mlx, (*game).mlx_win);
	mlx_destroy_display((*game).mlx);
	free((*game).mlx);
	free_game(game);
}
