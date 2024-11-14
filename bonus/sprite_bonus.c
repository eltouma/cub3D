/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:40:25 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/05 23:21:36 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

static void	animation(t_game *game, t_nsec t1);

// int clock_gettime(clockid_t clk_id, struct timespec *tp);
// struct timespec {
//     time_t tv_sec;  /* seconds */
//     long   tv_nsec; /* nanoseconds */ 1 000 000 000
// };
int	get_diff_ms(t_nsec nano, t_nsec t0)
{
	int	ms;

	ms = (nano.tv_nsec - t0.tv_nsec) / 1000000;
	ms = (nano.tv_sec - t0.tv_sec) * 1000 + ms;
	return (ms);
}

static void	animation(t_game *game, t_nsec t1)
{
	if (get_diff_ms(t1, (*game).t0) >= 300)
	{
		(*game).t0 = t1;
		if ((*game).frame == 0)
			(*game).sprite1 = &(*game).s1;
		else if ((*game).frame == 1)
		{
			(*game).sprite1 = &(*game).s2;
			(*game).sprite2 = &(*game).img_e;
		}
		else if ((*game).frame == 2)
			(*game).sprite1 = &(*game).s3;
		else
		{
			(*game).sprite1 = &(*game).s0;
			(*game).sprite2 = &(*game).img_n;
		}
		(*game).frame++;
		(*game).frame = (*game).frame % 4;
	}
}

int	anim_loop(t_game *game)
{
	t_nsec	t1;

	clock_gettime(CLOCK_MONOTONIC, &t1);
	(*game).t1 = t1;
	animation(game, t1);
	if ((*game).nb_doors > 0 && get_diff_ms(t1, (*game).t_door) > TD
		&& get_diff_ms(t1, (*game).t_door) <= TD + 100)
	{
		if ((*game).doors[(*game).door_idx].status == 1)
			(*game).doors[(*game).door_idx].status = 2;
		if ((*game).doors[(*game).door_idx].status == 3)
			(*game).doors[(*game).door_idx].status = 0;
	}
	mlx_destroy_image((*game).mlx, (*game).cub.img);
	init_cub(game);
	return (OK);
}
