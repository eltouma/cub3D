/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:15:28 by eltouma           #+#    #+#             */
/*   Updated: 2024/08/18 02:01:06 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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

// int	is_space_no_nl(char c)
// {
// 	if (c == 9 || (c >= 11 && c <= 12) || c == 32)
// 		return (1);
// 	return (0);
// }

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
