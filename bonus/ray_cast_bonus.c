/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 02:50:58 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/05 23:19:07 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

// -PI <= rad <= PI
double	ray(t_game *game, t_point p, double rad)
{
	double	rh;
	double	rv;
	t_point	mh;
	t_point	mv;

	if (rad >= -PI / 2 && rad <= PI / 2)
		rv = ray_inter_v2(game, p, rad, &mv);
	else
		rv = ray_inter_v(game, p, rad, &mv);
	if (rad >= 0)
		rh = ray_inter_h(game, p, rad, &mh);
	else
		rh = ray_inter_h2(game, p, rad, &mh);
	if (rh < rv)
	{
		(*game).horv = 'h';
		(*game).m = mh;
		return (rh);
	}
	else
	{
		(*game).horv = 'v';
		(*game).m = mv;
		return (rv);
	}
}

int	init_cub(t_game *game)
{
	(*game).cub.img = mlx_new_image((*game).mlx, (*game).cub.img_w,
			(*game).cub.img_h);
	(*game).cub.addr = mlx_get_data_addr((*game).cub.img, &(*game).cub.bpp,
			&(*game).cub.line_lgh, &(*game).cub.endian);
	if (!(*game).cub.img || !(*game).cub.addr)
		(free_init_cub(game), exit(KO));
	cubed(game, 0);
	return (OK);
}

// wall to draw from w during h
int	cubed(t_game *game, double rad)
{
	t_point	p;
	t_point	w;
	double	h;
	int		i;

	p.x = (*game).map.pos_x;
	p.y = (*game).map.pos_y;
	i = -(*game).cub.img_w / 2;
	while (i < (*game).cub.img_w / 2)
	{
		rad = mod2pi((*game).map.alpha - atan(i / (*game).d_proj));
		h = TS * (*game).cub.img_h / (ray(game, p, rad) * cos(atan(i
						/ (*game).d_proj)));
		w.y = (*game).cub.img_h / 2 - h / 2;
		w.x = i + (*game).cub.img_w / 2;
		draw_tex_line(*game, rad, h, w);
		(*game).lag = (t_point){0};
		w.y = 0;
		draw_s_line(&(*game).cub, w, (*game).cub.img_h / 2 - h / 2, (*game).cc);
		w.y = (*game).cub.img_h / 2 + h / 2 - 1;
		draw_v_line(&(*game).cub, w, (*game).cub.img_h / 2 - h / 2, (*game).cf);
		i++;
	}
	return (minimap(game), mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->cub.img, 0, 0), OK);
}

// if (ray_on_door(game) == 1 && game.door_status != 2)
t_img	compass(t_game game, double rad)
{
	if (ray_on_door(game) == 1)
		return (game.df);
	if (is_side_door(game, rad) == 1)
		return (game.ds);
	if ((game).horv == 'h')
	{
		if (0 <= rad && rad <= PI)
			return (*(game.sprite1));
		else
			return (game.img_s);
	}
	else
	{
		if (-PI / 2 <= rad && rad <= PI / 2)
			return (*(game.sprite2));
		else
			return (game.img_o);
	}
}

void	draw_tex_line(t_game game, double rad, int h, t_point w)
{
	t_img	tex;
	double	j;
	int		k;
	double	absc;

	tex = compass(game, rad);
	if (game.horv == 'h' && (0 <= rad && rad <= PI))
		absc = game.m.x - game.lag.x;
	else if (game.horv == 'h')
		absc = game.map.cols * TS - game.m.x + game.lag.x;
	else if (game.horv == 'v' && (-PI / 2 <= rad && rad <= PI / 2))
		absc = game.m.y - game.lag.y;
	else
		absc = game.map.rows * TS - game.m.y + game.lag.y;
	absc = (int)absc % TS + absc - (int)absc;
	absc = (absc / TS) * (tex.img_w);
	k = max(0, -(int)w.y);
	while (k < h)
	{
		j = k * ((double)tex.img_h / h);
		put_pixel_img(&game.cub, (int)w.x, (int)w.y + k, get_pix(tex, (int)j,
				(int)absc));
		k++;
	}
}
