/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 00:49:24 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/06 00:44:53 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

// Load images to play, and return a pointer (that could be NULL) for each
void	load_all_xpm(t_game *game)
{
	(*game).img_n.img = mlx_xpm_file_to_image((*game).mlx, (*game).data.north,
			&((*game).img_n.img_w), &((*game).img_n.img_h));
	(*game).img_s.img = mlx_xpm_file_to_image((*game).mlx, (*game).data.south,
			&((*game).img_s.img_w), &((*game).img_s.img_h));
	(*game).img_o.img = mlx_xpm_file_to_image((*game).mlx, (*game).data.west,
			&((*game).img_o.img_w), &((*game).img_o.img_h));
	(*game).img_e.img = mlx_xpm_file_to_image((*game).mlx, (*game).data.east,
			&((*game).img_e.img_w), &((*game).img_e.img_h));
	(*game).s0.img = mlx_xpm_file_to_image((*game).mlx, (*game).data.s0,
			&((*game).s0.img_w), &((*game).s0.img_h));
	(*game).s1.img = mlx_xpm_file_to_image((*game).mlx, (*game).data.s1,
			&((*game).s1.img_w), &((*game).s1.img_h));
	(*game).s2.img = mlx_xpm_file_to_image((*game).mlx, (*game).data.s2,
			&((*game).s2.img_w), &((*game).s2.img_h));
	(*game).s3.img = mlx_xpm_file_to_image((*game).mlx, (*game).data.s3,
			&((*game).s3.img_w), &((*game).s3.img_h));
	(*game).df.img = mlx_xpm_file_to_image((*game).mlx, (*game).data.door,
			&((*game).df.img_w), &((*game).df.img_h));
	(*game).ds.img = mlx_xpm_file_to_image((*game).mlx, (*game).data.side,
			&((*game).ds.img_w), &((*game).ds.img_h));
}

// Put all pointer from load in a tab to be checked later
void	load_tab_xpm(t_game *game)
{
	(*game).tab_img[0] = (*game).img_n.img;
	(*game).tab_img[1] = (*game).img_s.img;
	(*game).tab_img[2] = (*game).img_o.img;
	(*game).tab_img[3] = (*game).img_e.img;
	(*game).tab_img[4] = (*game).s0.img;
	(*game).tab_img[5] = (*game).s1.img;
	(*game).tab_img[6] = (*game).s2.img;
	(*game).tab_img[7] = (*game).s3.img;
	(*game).tab_img[8] = (*game).df.img;
	(*game).tab_img[9] = (*game).ds.img;
}

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
	mlx_destroy_image((*game).mlx, (*game).img_o.img);
	mlx_destroy_image((*game).mlx, (*game).img_e.img);
	mlx_destroy_image((*game).mlx, (*game).s0.img);
	mlx_destroy_image((*game).mlx, (*game).s1.img);
	mlx_destroy_image((*game).mlx, (*game).s2.img);
	mlx_destroy_image((*game).mlx, (*game).s3.img);
	mlx_destroy_image((*game).mlx, (*game).df.img);
	mlx_destroy_image((*game).mlx, (*game).ds.img);
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
	(*game).img_o.addr = mlx_get_data_addr((*game).img_o.img,
			&(*game).img_o.bpp, &(*game).img_o.line_lgh, &(*game).img_o.endian);
	(*game).s0.addr = mlx_get_data_addr((*game).s0.img, &(*game).s0.bpp,
			&(*game).s0.line_lgh, &(*game).s0.endian);
	(*game).s1.addr = mlx_get_data_addr((*game).s1.img, &(*game).s1.bpp,
			&(*game).s1.line_lgh, &(*game).s1.endian);
	(*game).s2.addr = mlx_get_data_addr((*game).s2.img, &(*game).s2.bpp,
			&(*game).s2.line_lgh, &(*game).s2.endian);
	(*game).s3.addr = mlx_get_data_addr((*game).s3.img, &(*game).s3.bpp,
			&(*game).s3.line_lgh, &(*game).s3.endian);
	(*game).df.addr = mlx_get_data_addr((*game).df.img, &(*game).df.bpp,
			&(*game).df.line_lgh, &(*game).df.endian);
	(*game).ds.addr = mlx_get_data_addr((*game).ds.img, &(*game).ds.bpp,
			&(*game).ds.line_lgh, &(*game).ds.endian);
}
