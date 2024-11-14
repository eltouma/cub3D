/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 21:34:52 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/02 00:55:21 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	get_data(char *argv1, t_data *data)
{
	int		fd;
	char	*str;

	fd = open(argv1, O_RDONLY);
	if (fd == -1)
		return (perror("cub3D"), KO);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			return (free(str), close(fd), OK);
		if (!is_map_line(str))
		{
			if (parse_data_line(str, data) == KO)
				return (free_data(data), free(str), close(fd), KO);
		}
		free(str);
	}
	if (close(fd) == -1)
		return (perror("cub3D"), KO);
}

int	check_ceil(char *str, t_data *data)
{
	if (count_comma(str) == 2)
	{
		if ((*data).ceil_dup == 1)
			return (err_msg(EDUP), KO);
		(*data).ceil_dup = 1;
		return (fill_ceil(str, data));
	}
	else if (count_comma(str) < 2)
		return (err_msg(ECMI), KO);
	else
		return (err_msg(EUNC), KO);
}

int	check_floor(char *str, t_data *data)
{
	if (count_comma(str) == 2)
	{
		if ((*data).floor_dup == 1)
			return (err_msg(EDUP), KO);
		(*data).floor_dup = 1;
		return (fill_floor(str, data));
	}
	else if (count_comma(str) < 2)
		return (err_msg(ECMI), KO);
	else
		return (err_msg(EUNC), KO);
}

// str != NULL, worst case (how ?), is_empty manage that
int	parse_data_line(char *str, t_data *data)
{
	int	i;

	if (is_empty(str) == 1)
		return (OK);
	i = 0;
	while (str[i] && is_space(str[i]) == 1)
		i++;
	if (str[i] && str[i] == 'N' && str[i + 1] == 'O')
		return (check_no(str, data));
	if (str[i] && str[i] == 'S' && str[i + 1] == 'O')
		return (check_so(str, data));
	if (str[i] && str[i] == 'W' && str[i + 1] == 'E')
		return (check_we(str, data));
	if (str[i] && str[i] == 'E' && str[i + 1] == 'A')
		return (check_ea(str, data));
	if (str[i] == 'C')
		return (check_ceil(str, data));
	if (str[i] == 'F')
		return (check_floor(str, data));
	return (err_msg(EWRS), KO);
}
