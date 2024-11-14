/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 21:44:36 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/02 01:45:13 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	get_screen_size(t_game *game)
{
	int	screen_w;
	int	screen_h;

	(*game).win_w = WIN_W;
	(*game).win_h = WIN_H;
	mlx_get_screen_size((*game).mlx, &screen_w, &screen_h);
	if (screen_w < WIN_W || screen_h < WIN_H)
	{
		(*game).win_w = screen_w;
		(*game).win_h = screen_h;
	}
}

void	set_img_size(t_game *game)
{
	(*game).cub.img_w = (*game).win_w;
	(*game).cub.img_h = (*game).win_h;
	(*game).d_proj = (double)(*game).cub.img_w / (2 * tan(FOV / 2));
}

int	init_mlx(t_game *game)
{
	(*game).mlx = mlx_init();
	if (!(*game).mlx)
		return (err_msg(EMCIM), KO);
	(get_screen_size(game), set_img_size(game));
	(*game).mlx_win = mlx_new_window((*game).mlx, (*game).win_w, (*game).win_h,
			"cub3D");
	if (!(*game).mlx_win)
	{
		err_msg(EMCGW);
		mlx_destroy_display((*game).mlx);
		free((*game).mlx);
		return (KO);
	}
	start_game(game);
	return (OK);
}

void	set_colors(t_game *game)
{
	(*game).cc = create_trgb(0, (*game).data.ceil[0], (*game).data.ceil[1],
			(*game).data.ceil[2]);
	(*game).cf = create_trgb(0, (*game).data.floor[0],
			(*game).data.floor[1], (*game).data.floor[2]);
}

/*
void	start_game(t_game *game)
{
	xpm_loader(game);
	set_colors(game);
	init_events(game);
	init_cub(game);
	mlx_loop((*game).mlx);
}
*/

void	xpm_loader(t_game *game)
{
	load_all_xpm(game);
	load_tab_xpm(game);
	if (check_tab_xpm(game) == KO)
	{
		err_msg(ELOAD);
		destroy_tab_xpm(game);
		mlx_destroy_window((*game).mlx, (*game).mlx_win);
		mlx_destroy_display((*game).mlx);
		free((*game).mlx);
		free_game(game);
		exit(KO);
	}
	get_all_addr(game);
}
