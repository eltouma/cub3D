/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_data_utils1_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 21:34:52 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/06 00:45:10 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

int	parse_data_line_no(char *str, t_data *data)
{
	if ((*data).north)
		return (err_msg(EDUP), KO);
	return (get_path(str, data, 'N'), OK);
}

int	parse_data_line_so(char *str, t_data *data)
{
	if ((*data).south)
		return (err_msg(EDUP), KO);
	return (get_path(str, data, 'S'), OK);
}

int	parse_data_line_we(char *str, t_data *data)
{
	if ((*data).west)
		return (err_msg(EDUP), KO);
	return (get_path(str, data, 'W'), OK);
}

int	parse_data_line_ea(char *str, t_data *data)
{
	if ((*data).east)
		return (err_msg(EDUP), KO);
	return (get_path(str, data, 'E'), OK);
}

int	parse_data_line_df(char *str, t_data *data)
{
	if ((*data).door)
		return (err_msg(EDUP), KO);
	return (get_path(str, data, 'F'), OK);
}
