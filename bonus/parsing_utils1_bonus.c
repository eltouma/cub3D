/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:15:28 by eltouma           #+#    #+#             */
/*   Updated: 2024/10/06 00:45:31 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

// path malloc'ed --> to be free'd
// get path after the spaces, the NO/SO/WE/EA, and spaces
// path can received "" --> good to avoid duplicate NO with no path
// path == NULL only when malloc failled
// validity of the path to be checked after
// i = i + 2 --> to skip NO
void	get_path(char *str, t_data *data, char card)
{
	int	i;

	i = 0;
	while (str[i] && is_space(str[i]) == 1)
		i++;
	if (str[i] && str[i + 1])
		i = i + 2;
	while (str[i] && is_space(str[i]) == 1)
		i++;
	if (card == 'N')
		(*data).north = ft_substr(str, i, ft_strlen(str));
	if (card == 'S')
		(*data).south = ft_substr(str, i, ft_strlen(str));
	if (card == 'W')
		(*data).west = ft_substr(str, i, ft_strlen(str));
	if (card == 'E')
		(*data).east = ft_substr(str, i, ft_strlen(str));
	get_path2(str, data, card, i);
}

void	get_path2(char *str, t_data *data, char card, int i)
{
	if (card == 'F')
		(*data).door = ft_substr(str, i, ft_strlen(str));
	if (card == 'D')
		(*data).side = ft_substr(str, i, ft_strlen(str));
	if (card == '0')
		(*data).s0 = ft_substr(str, i, ft_strlen(str));
	if (card == '1')
		(*data).s1 = ft_substr(str, i, ft_strlen(str));
	if (card == '2')
		(*data).s2 = ft_substr(str, i, ft_strlen(str));
	if (card == '3')
		(*data).s3 = ft_substr(str, i, ft_strlen(str));
}

// fill the ceil tab with the colors
// ft_atoi_cub limit color to an int
int	fill_ceil(char *str, t_data *data)
{
	int		i;
	int		j;
	char	**colors;

	i = 0;
	while (str[i] && (is_space(str[i]) == 1 || str[i] == 'C'))
		i++;
	colors = ft_split(str + i, ',');
	if (!colors)
		return (KO);
	i = 0;
	j = 0;
	while (colors[i])
	{
		if (i > 3)
			return (err_msg(EUNC), double_free(colors), KO);
		(*data).ceil[j] = ft_atoi_cub(colors[i]);
		if ((*data).ceil[j] > 255 || (*data).ceil[j] < 0)
			return (err_msg(EUNC), double_free(colors), KO);
		i += 1;
		j += 1;
	}
	return (double_free(colors), OK);
}

// fill the floor tab with the colors
// ft_atoi_cub limit color to an int
int	fill_floor(char *str, t_data *data)
{
	int		i;
	int		j;
	char	**colors;

	i = 0;
	while (str[i] && (is_space(str[i]) == 1 || str[i] == 'F'))
		i++;
	colors = ft_split(str + i, ',');
	if (!colors)
		return (KO);
	i = 0;
	j = 0;
	while (colors[i])
	{
		if (i > 3)
			return (err_msg(EUNC), double_free(colors), KO);
		(*data).floor[j] = ft_atoi_cub(colors[i]);
		if ((*data).floor[j] > 255 || (*data).floor[j] < 0)
			return (err_msg(EUNC), double_free(colors), KO);
		i += 1;
		j += 1;
	}
	return (double_free(colors), OK);
}
