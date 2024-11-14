/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 03:14:22 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/01 21:59:03 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_path(t_data *data)
{
	if (!is_valid_path(&(*data).north) || !is_valid_path(&(*data).south)
		|| !is_valid_path(&(*data).west) || !is_valid_path(&(*data).east))
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

// is_valid_path must be called first to compare the subpath
// and not the path (not clean as subpath is) from get_path
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
