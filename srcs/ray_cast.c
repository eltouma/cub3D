/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 02:50:58 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/19 22:29:56 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// -PI <= rad <= PI
double	ray(t_map map, t_point p, double rad, t_game *game)
{
	double	rh;
	double	rv;
	t_point	mh;
	t_point	mv;

	if (rad >= -PI / 2 && rad <= PI / 2)
		rv = ray_inter_v2(map, p, rad, &mv);
	else
		rv = ray_inter_v(map, p, rad, &mv);
	if (rad >= 0)
		rh = ray_inter_h(map, p, rad, &mh);
	else
		rh = ray_inter_h2(map, p, rad, &mh);
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

void	init_cub(t_game *game)
{
	(*game).cub.img = mlx_new_image((*game).mlx, (*game).cub.img_w,
			(*game).cub.img_h);
	(*game).cub.addr = mlx_get_data_addr((*game).cub.img, &(*game).cub.bpp,
			&(*game).cub.line_lgh, &(*game).cub.endian);
	cubed(game);
}

// 0xFAE0E4
// 0xFF85A1
void	cubed(t_game *game)
{
	t_point	p;
	t_point	w;
	double	rad;
	double	h;
	int		i;

	p.x = (*game).map.pos_x;
	p.y = (*game).map.pos_y;
	i = -(*game).cub.img_w / 2;
	while (i < (*game).cub.img_w / 2)
	{
		rad = mod2pi((*game).map.alpha - atan(i / (*game).d_proj));
		h = TS * (*game).cub.img_h / (ray((*game).map, p, rad, game)
				* cos(atan(i / (*game).d_proj)));
		w.y = (*game).cub.img_h / 2 - h / 2;
		w.x = i + (*game).cub.img_w / 2;
		draw_tex_line(*game, rad, h, w);
		w.y = 0;
		draw_v_line(&(*game).cub, w, (*game).cub.img_h / 2 - h / 2, (*game).cc);
		w.y = (*game).cub.img_h / 2 + h / 2 - 1;
		draw_v_line(&(*game).cub, w, (*game).cub.img_h / 2 - h / 2, (*game).cf);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->cub.img, 0, 0);
}

// From a point W, go down (j increases), drawing pixel by pixel, till lenght h
// int j; // src
// int k; // dest
// fit en hauteur et // fit en largeur
void	draw_tex_line(t_game game, double rad, int h, t_point w)
{
	t_img	tex;
	double	j;
	int		k;
	double	absc;

	tex = compass(game, rad);
	if (game.horv == 'h' && (0 <= rad && rad <= PI))
		absc = game.m.x;
	else if (game.horv == 'h')
		absc = game.map.cols * TS - game.m.x;
	else if (game.horv == 'v' && (-PI / 2 <= rad && rad <= PI / 2))
		absc = game.m.y;
	else
		absc = game.map.rows * TS - game.m.y;
	absc = (int)absc % TS + absc - (int)absc;
	absc = (absc / TS) * (tex.img_w);
	k = 0;
	while (k < h)
	{
		j = k * ((double)tex.img_h / h);
		put_pixel_img(&game.cub, (int)w.x, (int)w.y + k, get_pix(tex, (int)j,
				(int)absc));
		k++;
	}
}

t_img	compass(t_game game, double rad)
{
	if (game.horv == 'h')
	{
		if (0 <= rad && rad <= PI)
			return (game.img_n);
		else
			return (game.img_s);
	}
	else
	{
		if (-PI / 2 <= rad && rad <= PI / 2)
			return (game.img_e);
		else
			return (game.img_w);
	}
}
