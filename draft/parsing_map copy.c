/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 22:01:45 by caguillo          #+#    #+#             */
/*   Updated: 2024/08/17 00:34:38 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// In the scene, is the map well at the end ?
// Empty lines after the map are accepted
// if str == NULL, end of file ? or error gnl ?
// --> so need to count the lines to separate those cases
int	is_map_last(char *argv1, int fd)
{
	char	*str;
	int		is_map;
	int		n;
	int		i;
	int		end_map;

	is_map = 0;
	end_map = 0;
	if (fd == -1)
		return (putstr_fd(EOPN, 2), 0);
	n = count_line(argv1); // printf("%d\n", n);
	if (n == -1)
		return (close(fd), 0);
	if (n == 0)
		return (putstr_fd(EEMP, 2), close(fd), 0);
	i = 0;
	while (i < n)
	{
		str = get_next_line(fd);
		// printf("%s", str);
		if (!str)
			return (putstr_fd(EGAL, 2), close(fd), 0);
		if (is_not_empty(str))
		{
			if (end_map == 1)
				return (putstr_fd(ELAM, 2), free(str), close(fd), 0);
			if (is_map_line(str) == 1)
				is_map = 1;
			if (is_map_line(str) == 0 && is_map == 1)
				return (putstr_fd(ELAM, 2), free(str), close(fd), 0);
		}
		if (!is_not_empty(str) && is_map == 1)
			end_map = 1;
		// if ((!is_not_empty(str) || str[0] == 0) && is_map == 1)
		// 	end_map = 1;
		// if ((str[0] == 0) && is_map == 1)
		// {
		// 	printf("la\n");
		// 	end_map = 1;
		// }
		free(str);
		i++;
	}
	if (is_map == 0)
		return (putstr_fd(ENOM, 2), close(fd), 0);
	if (close(fd) == -1)
		return (putstr_fd(EGAL, 2), 0);
	return (1);
}

// Count the number of lines in a scene (--> for gnl loop)
// Need to open and close the file
int	count_line(char *argv1)
{
	int		n;
	char	*str;
	int		fd;

	fd = open(argv1, O_RDONLY);
	if (fd == -1)
		return (putstr_fd(EOPN, 2), -1);
	n = 0;
	while (1)
	{
		str = get_next_line(fd);
		// printf("ici %s\n", str);
		if (!str)
			break ;
		free(str);
		n++;
	}
	// free(str);
	if (close(fd) == -1)
		return (putstr_fd(EGAL, 2), -1);
	return (n);
}

// Is 'str' not_empty
// empty means here nothing or only spaces
// 0 = empty
// ____0 =  empty
// tabtab_0 = empty
int	is_not_empty(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (is_space(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

// Is the line 'str' a line that could be a line of a map
// A line is a line of a map if at least there are two '1'
// and only characters authorised inside a map
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
	if (is_one < 2)
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
