/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 22:01:45 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/03 02:20:23 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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

// int	is_map_last(char *argv1)
// {
// 	char	*str;
// 	int		is_map;
// 	int		end_map;
// 	int		fd;

// 	fd = open(argv1, O_RDONLY);
// 	if (fd == -1)
// 		return (perror("cub3D"), 0);
// 	is_map = 0;
// 	end_map = 0;
// 	while (1)
// 	{
// 		str = get_next_line(fd);
// 		if (!str && is_map == 1)
// 			return (close(fd), 1);
// 		if (!str)
// 			return (err_msg(ENOM), close(fd), 0);
// 		if (!is_empty(str))
// 		{
// 			if (end_map == 1)
// 				return (err_msg(ELAM), free(str), close(fd), 0);
// 			if (is_map_line(str) == 1)
// 				is_map = 1;
// 			if (is_map_line(str) == 0 && is_map == 1)
// 				return (err_msg(ELAM), free(str), close(fd), 0);
// 		}
// 		if (is_empty(str) && is_map == 1)
// 			end_map = 1;
// 		free(str);
// 	}
// }
