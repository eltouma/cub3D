/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:20:12 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/05 22:16:13 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

void	free_data(t_data *data)
{
	free((*data).north);
	free((*data).south);
	free((*data).west);
	free((*data).east);
	free((*data).door);
	free((*data).side);
	free((*data).s0);
	free((*data).s1);
	free((*data).s2);
	free((*data).s3);
}

void	free_game(t_game *game)
{
	free_data(&((*game).data));
	double_free((*game).map.tab);
	free((*game).doors);
}

void	free_cub(t_game *game)
{
	destroy_all_xpm(game);
	mlx_destroy_image((*game).mlx, (*game).cub.img);
	mlx_destroy_window((*game).mlx, (*game).mlx_win);
	mlx_destroy_display((*game).mlx);
	free((*game).mlx);
	free_game(game);
}

// mlx_destroy_image((*game).mlx, (*game).cub.img);
void	free_init_cub(t_game *game)
{
	err_msg(EIIMG);
	destroy_all_xpm(game);
	mlx_destroy_window((*game).mlx, (*game).mlx_win);
	mlx_destroy_display((*game).mlx);
	free((*game).mlx);
	free_game(game);
}
