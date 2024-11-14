/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_xpm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 00:49:24 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/01 22:48:18 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// In case of at least one NULL in the tab,
// will destroy only the image well loaded (not NULL)
void	destroy_tab_xpm(t_game *game)
{
	int	i;

	i = 0;
	while (i < IMG_NBR)
	{
		if ((*game).tab_img[i])
			mlx_destroy_image((*game).mlx, (*game).tab_img[i]);
		i++;
	}
}

void	destroy_all_xpm(t_game *game)
{
	mlx_destroy_image((*game).mlx, (*game).img_n.img);
	mlx_destroy_image((*game).mlx, (*game).img_s.img);
	mlx_destroy_image((*game).mlx, (*game).img_w.img);
	mlx_destroy_image((*game).mlx, (*game).img_e.img);
}
