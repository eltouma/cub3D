/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 22:01:45 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/01 23:24:59 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// is the scene is not empty and contains only
// empty lines, map lines or data lines
int	is_scene(char *argv1)
{
	int		fd;
	char	*str;
	int		empty;

	fd = open(argv1, O_RDONLY);
	if (fd == -1)
		return (perror("cub3D"), 0);
	empty = 1;
	while (1)
	{
		str = get_next_line(fd);
		if (!str && empty == 0)
			return (close(fd), 1);
		if (!str)
			return (err_msg(ESEM), close(fd), 0);
		empty = 0;
		if (!is_empty(str) && !is_map_line(str) && !is_data_line(str))
			return (err_msg(EUNS), free(str), close(fd), 0);
		free(str);
	}
}

// spacesNO/SO/WE/EA/F/C(can be space)next
int	is_data_line(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && is_space(str[i]) == 1)
		i++;
	if (str[i] == 'C')
		return (1);
	if (str[i] == 'F')
		return (1);
	if (str[i] && str[i] == 'N' && str[i + 1] == 'O')
		return (1);
	if (str[i] && str[i] == 'S' && str[i + 1] == 'O')
		return (1);
	if (str[i] && str[i] == 'W' && str[i + 1] == 'E')
		return (1);
	if (str[i] && str[i] == 'E' && str[i + 1] == 'A')
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

// Is the line 'str' a line that could be a line of a map
// A line is a line of a map if at least there are two '1'
// and only characters authorised inside a map
// do not check the validity of the map_line --> later, with error msg needed
int	is_map_line(char *str)
{
	int	i;
	int	is_one;

	if (!str)
		return (0);
	is_one = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '1')
			is_one++;
		if (is_map_char(str[i]) == 0)
			return (0);
		i++;
	}
	if (is_one < 1)
		return (0);
	return (1);
}

// Characters authorised inside a map
int	is_map_char(char c)
{
	if (c == '0' || c == '1')
		return (1);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	if (is_space(c) == 1)
		return (1);
	return (0);
}
