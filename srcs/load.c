/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 00:49:24 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/01 22:48:47 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// Load images to play, and return a pointer (that could be NULL) for each
void	load_all_xpm(t_game *game)
{
	(*game).img_n.img = mlx_xpm_file_to_image((*game).mlx, (*game).data.north,
			&((*game).img_n.img_w), &((*game).img_n.img_h));
	(*game).img_s.img = mlx_xpm_file_to_image((*game).mlx, (*game).data.south,
			&((*game).img_s.img_w), &((*game).img_s.img_h));
	(*game).img_w.img = mlx_xpm_file_to_image((*game).mlx, (*game).data.west,
			&((*game).img_w.img_w), &((*game).img_w.img_h));
	(*game).img_e.img = mlx_xpm_file_to_image((*game).mlx, (*game).data.east,
			&((*game).img_e.img_w), &((*game).img_e.img_h));
}

// Put all pointer from load in a tab to be checked later
void	load_tab_xpm(t_game *game)
{
	(*game).tab_img[0] = (*game).img_n.img;
	(*game).tab_img[1] = (*game).img_s.img;
	(*game).tab_img[2] = (*game).img_w.img;
	(*game).tab_img[3] = (*game).img_e.img;
}

// Check if there is a NULL inside the tab
int	check_tab_xpm(t_game *game)
{
	int	i;

	i = 0;
	while (i < IMG_NBR)
	{
		if (!(*game).tab_img[i])
			return (KO);
		i++;
	}
	return (OK);
}

// In case of right loading (no NULL), get the addr char * of the loaded images
// in order to take pixels of those images
void	get_all_addr(t_game *game)
{
	(*game).img_n.addr = mlx_get_data_addr((*game).img_n.img,
			&(*game).img_n.bpp, &(*game).img_n.line_lgh, &(*game).img_n.endian);
	(*game).img_s.addr = mlx_get_data_addr((*game).img_s.img,
			&(*game).img_s.bpp, &(*game).img_s.line_lgh, &(*game).img_s.endian);
	(*game).img_e.addr = mlx_get_data_addr((*game).img_e.img,
			&(*game).img_e.bpp, &(*game).img_e.line_lgh, &(*game).img_e.endian);
	(*game).img_w.addr = mlx_get_data_addr((*game).img_w.img,
			&(*game).img_w.bpp, &(*game).img_w.line_lgh, &(*game).img_w.endian);
}
