/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:08:58 by eltouma           #+#    #+#             */
/*   Updated: 2024/10/01 22:44:00 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	handle_close(t_game *game)
{
	free_cub(game);
	exit(OK);
}

int	handle_key(int key_code, t_game *game)
{
	if (key_code == XK_Escape || key_code == KEY_Q)
		handle_close(game);
	if (key_code == KEY_W)
		move_dir(game, STEP);
	if (key_code == KEY_S)
		move_dir(game, -STEP);
	if (key_code == KEY_A)
		move_dir2(game, STEP);
	if (key_code == KEY_D)
		move_dir2(game, -STEP);
	if (key_code == KEY_LEFT)
		move_alpha(game, STEP_ALPHA);
	if (key_code == KEY_RIGHT)
		move_alpha(game, -STEP_ALPHA);
	if (key_code == KEY_UP)
		move_dir(game, STEP);
	if (key_code == KEY_DOWN)
		move_dir(game, -STEP);
	return (OK);
}

// mlx_key_hook alias of mlx_hook + KeyPress
void	init_events(t_game *game)
{
	mlx_hook((*game).mlx_win, KeyPress, KeyPressMask, handle_key, game);
	mlx_hook((*game).mlx_win, DestroyNotify, NoEventMask, handle_close, game);
}

// should be enough, as soon as out of range, put back inside the range
double	mod2pi(double rad)
{
	if (rad > PI)
		return (rad - 2 * PI);
	if (rad < -PI)
		return (rad + 2 * PI);
	return (rad);
}
