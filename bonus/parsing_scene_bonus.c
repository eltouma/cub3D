/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 22:01:45 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/05 22:23:19 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

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
	if (str[i] && ((str[i] == 'C') || (str[i] == 'F')))
		return (1);
	if (str[i] && str[i] == 'N' && str[i + 1] == 'O')
		return (1);
	if (str[i] && str[i] == 'S' && str[i + 1] == 'O')
		return (1);
	if (str[i] && str[i] == 'W' && str[i + 1] == 'E')
		return (1);
	if (str[i] && str[i] == 'E' && str[i + 1] == 'A')
		return (1);
	if (str[i] && ((str[i] == 'D' && str[i + 1] == 'F') || (str[i] == 'D'
				&& str[i + 1] == 'S') || (str[i] == 'S' && str[i + 1] == '0')
			|| (str[i] == 'S' && str[i + 1] == '1')))
		return (1);
	if ((str[i] && str[i] == 'S' && str[i + 1] == '2') || (str[i]
			&& str[i] == 'S' && str[i + 1] == '3'))
		return (1);
	return (0);
}

// In the scene, is the map well at the end ?
// Empty lines after the map are accepted
// Norme : if str == NULL from GNL => end of file
// return (0) at the end, because should not be reached, if reached = issue.
int	is_map_last(char *argv1, int is_map, int end_map, int fd)
{
	char	*str;

	fd = open(argv1, O_RDONLY);
	if (fd == -1)
		return (perror("cub3D"), 0);
	while (1)
	{
		str = get_next_line(fd);
		if (!str && is_map == 1)
			return (close(fd), 1);
		if (!str)
			return (err_msg(ENOM), close(fd), 0);
		if (!is_empty(str))
		{
			if (end_map == 1)
				return (err_msg(ELAM), free(str), close(fd), 0);
			if (is_map_line(str) == 1)
				is_map = 1;
			if (is_map_line(str) == 0 && is_map == 1)
				return (err_msg(ELAM), free(str), close(fd), 0);
		}
		if (is_empty(str) && is_map == 1)
			end_map = 1;
		free(str);
	}
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
// if (is_space(c) == 1 && c != '\t') --> to not valid/accept tab
int	is_map_char(char c)
{
	if (c == '0' || c == '1')
		return (1);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	if (c == 'D')
		return (1);
	if (is_space(c) == 1)
		return (1);
	return (0);
}
