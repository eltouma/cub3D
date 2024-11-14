/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_path_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 03:14:22 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/05 22:40:13 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

int	check_path(t_data *data)
{
	if (!is_valid_path(&(*data).north) || !is_valid_path(&(*data).south)
		|| !is_valid_path(&(*data).west) || !is_valid_path(&(*data).east))
		return (free_data(data), KO);
	if (!is_valid_path(&(*data).door) || !is_valid_path(&(*data).side)
		|| !is_valid_path(&(*data).s0) || !is_valid_path(&(*data).s1)
		|| !is_valid_path(&(*data).s2) || !is_valid_path(&(*data).s3))
		return (free_data(data), KO);
	if (is_dup_path(data) == 1)
		return (free_data(data), KO);
	return (OK);
}

// a valid format path should be = path.xpmSpaces\n
// get_path removed spaces before, send NULL or "" or (blabla)(\n)\0
// Need to send a pointer on path as i amend path
int	is_valid_path(char **path)
{
	int		i;
	char	*subpath;

	if (!(*path) || (*path)[0] == 0)
		return (err_msg(EPMI), 0);
	i = 0;
	while ((*path)[i] && is_space((*path)[i]) == 0)
		i++;
	subpath = ft_substr(*path, 0, i);
	while ((*path)[i])
	{
		if (is_space((*path)[i]) == 0)
			return (free(subpath), err_msg(EWRP), 0);
		i++;
	}
	if (check_file_ext(subpath, ".xpm") == KO)
		return (free(subpath), err_msg(EUNP), 0);
	free(*path);
	*path = ft_strdup(subpath);
	return (free(subpath), 1);
}
// printf("%s", *path);
// printf("subpath %s\n\n", subpath);
// printf("avant %s", path);
// printf("avant subpath %s\n", subpath);
// printf("apres free %s\n", path);

// is_valid_path must be called first to compare the subpath
// and not the path (not clean as subpath is) from get_path
// only for the 4 directions (we can dup for others)
int	is_dup_path(t_data *data)
{
	if (ft_strcmp((*data).north, (*data).south) == 0)
		return (err_msg(EDPA), 1);
	if (ft_strcmp((*data).north, (*data).west) == 0)
		return (err_msg(EDPA), 1);
	if (ft_strcmp((*data).north, (*data).east) == 0)
		return (err_msg(EDPA), 1);
	if (ft_strcmp((*data).south, (*data).west) == 0)
		return (err_msg(EDPA), 1);
	if (ft_strcmp((*data).south, (*data).east) == 0)
		return (err_msg(EDPA), 1);
	if (ft_strcmp((*data).west, (*data).east) == 0)
		return (err_msg(EDPA), 1);
	return (0);
}
