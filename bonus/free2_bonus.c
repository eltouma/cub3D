/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:06:40 by eltouma           #+#    #+#             */
/*   Updated: 2024/10/02 08:25:39 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

void	putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	err_msg(char *str)
{
	putstr_fd(str, 2);
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
