/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_data_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 21:34:52 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/02 00:55:07 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_no(char *str, t_data *data)
{
	if ((*data).north)
		return (err_msg(EDUP), KO);
	return (get_path(str, data, 'N'), OK);
}

int	check_so(char *str, t_data *data)
{
	if ((*data).south)
		return (err_msg(EDUP), KO);
	return (get_path(str, data, 'S'), OK);
}

int	check_we(char *str, t_data *data)
{
	if ((*data).west)
		return (err_msg(EDUP), KO);
	return (get_path(str, data, 'W'), OK);
}

int	check_ea(char *str, t_data *data)
{
	if ((*data).east)
		return (err_msg(EDUP), KO);
	return (get_path(str, data, 'E'), OK);
}
