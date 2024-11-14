/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:15:28 by eltouma           #+#    #+#             */
/*   Updated: 2024/10/26 00:56:35 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	count_words(char *str, char c)
{
	unsigned int	i;
	int				j;

	i = 0;
	j = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] != c)
			j += 1;
		while (str[i] != c && str[i] != '\0')
			i += 1;
		while (str[i] == c && str[i] != '\0')
			i += 1;
	}
	return (j);
}

int	count_size_of_word(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i += 1;
	return (i);
}

static char	*fill_tab(char *str, char c)
{
	int		i;
	int		size;
	char	*s;

	i = 0;
	if (!str)
		return (NULL);
	size = count_size_of_word(str, c);
	s = (char *)malloc(sizeof(char) * size + 1);
	if (!s)
		return (NULL);
	while (str[i] != '\0' && str[i] != c)
	{
		s[i] = str[i];
		i += 1;
	}
	s[i] = '\0';
	return (s);
}

static char	**return_tab(char *str, char c)
{
	char	**tab;

	if (!str)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (!tab)
		return (NULL);
	return (tab);
}

// if (!str)
// 	return (NULL); --> done in return_tab
char	**ft_split(char *str, char c)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	tab = return_tab(str, c);
	if (!tab)
		return (NULL);
	tab[count_words(str, c)] = NULL;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			tab[j] = fill_tab(&str[i], c);
			if (!tab[j])
				return (free_tab(tab));
			j += 1;
			while (str[i] != '\0' && str[i] != c)
				i += 1;
		}
		else
			i += 1;
	}
	return (tab);
}
