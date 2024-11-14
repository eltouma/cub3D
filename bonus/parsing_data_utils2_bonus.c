/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_data_utils2_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 21:34:52 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/05 22:38:00 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

int	parse_data_line_ds(char *str, t_data *data)
{
	if ((*data).side)
		return (err_msg(EDUP), KO);
	return (get_path(str, data, 'D'), OK);
}

int	parse_data_line_s0(char *str, t_data *data)
{
	if ((*data).s0)
		return (err_msg(EDUP), KO);
	return (get_path(str, data, '0'), OK);
}

int	parse_data_line_s1(char *str, t_data *data)
{
	if ((*data).s1)
		return (err_msg(EDUP), KO);
	return (get_path(str, data, '1'), OK);
}

int	parse_data_line_s2(char *str, t_data *data)
{
	if ((*data).s2)
		return (err_msg(EDUP), KO);
	return (get_path(str, data, '2'), OK);
}

int	parse_data_line_s3(char *str, t_data *data)
{
	if ((*data).s3)
		return (err_msg(EDUP), KO);
	return (get_path(str, data, '3'), OK);
}
