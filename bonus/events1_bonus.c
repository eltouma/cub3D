/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:08:58 by eltouma           #+#    #+#             */
/*   Updated: 2024/10/02 16:32:34 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

// mlx_key_hook alias of mlx_hook + KeyPress
void	init_events(t_game *game)
{
	mlx_hook((*game).mlx_win, KeyPress, KeyPressMask, handle_key, game);
	mlx_hook((*game).mlx_win, DestroyNotify, NoEventMask, handle_close, game);
	mlx_hook(game->mlx_win, MotionNotify, PointerMotionMask, handle_mouse,
		game);
	mlx_loop_hook((*game).mlx, anim_loop, game);
}

int	handle_mouse(int x, int y, t_game *game)
{
	static int	prev_x = WIN_W / 2;

	(void)y;
	if (x - prev_x > SPEED_MOUSE)
		move_alpha(game, -SPEED_MOUSE);
	else if (x - prev_x < -SPEED_MOUSE)
		move_alpha(game, SPEED_MOUSE);
	prev_x = x;
	return (OK);
}
// printf("x = %d, y = %d\n", x, y);

int	handle_close(t_game *game)
{
	free_cub(game);
	exit(OK);
}

int	handle_key(int key_code, t_game *game)
{
	if (key_code == XK_Escape)
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
	if (key_code == KEY_M)
		(*game).mini_maxi++;
	if (key_code == KEY_SPACE && (*game).nb_doors > 0)
		move_door(game);
	return (OK);
}

void	move_dir(t_game *game, int step)
{
	t_point	p;
	double	rad;

	rad = (*game).map.alpha;
	p.x = (*game).map.pos_x + round(step * cos(rad));
	p.y = (*game).map.pos_y - round(step * sin(rad));
	if (is_wall((*game).map, p) == 0)
	{
		if (is_corner((*game).map, p) == 0)
		{
			if (is_door_closed(*game, p) == 0)
			{
				(*game).map.pos_x = p.x;
				(*game).map.pos_y = p.y;
				mlx_destroy_image((*game).mlx, (*game).cub.img);
				init_cub(game);
			}
		}
	}
}
// printf("pos x = %ld\n", (*game).map.pos_x);
// printf("pos y = %ld\n", (*game).map.pos_y);
