/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:15:28 by eltouma           #+#    #+#             */
/*   Updated: 2024/10/03 00:34:13 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

int	count_comma(char *str)
{
	int	i;
	int	count;

	if (!str)
		return (0);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	is_number(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

// Is 'str' empty
// empty means here nothing (NULL) or only all spaces (9-13 32)
// 0 = empty // ____0 =  empty // tabtab_0 = empty // 0\n = empty
int	is_empty(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (is_space(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

// int	is_space_no_nl(char c)
// {
// 	if (c == 9 || (c >= 11 && c <= 12) || c == 32)
// 		return (1);
// 	return (0);
// }
