/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 01:47:05 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/03 02:15:46 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] - s2[i] == 0)
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*dup;

	if (!str)
		return (NULL);
	dup = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// Get the color of the pixel, i.e. the pixel, from a texture, hit on M
// at z altitude on the abscise M.x (case h) or M.y (case v)
unsigned int	get_pix(t_img tex, int z, int absc)
{
	unsigned int	color;

	if (absc < tex.img_w && z < tex.img_h)
		color = *(unsigned int *)(tex.addr + (z * tex.line_lgh + absc
					* sizeof(int)));
	else
		color = 0;
	return (color);
}
