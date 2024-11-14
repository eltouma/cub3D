/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 02:50:58 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/01 20:10:36 by caguillo         ###   ########.fr       */
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

	// (*game).lag = 0;
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
	// draw_angle_line(&img, p, rad, rv);
	// draw_angle_line(&img, p, rad, rh);
}

int	init_cub(t_game *game)
{
	(*game).cub.img = mlx_new_image((*game).mlx, (*game).cub.img_w,
			(*game).cub.img_h);
	(*game).cub.addr = mlx_get_data_addr((*game).cub.img, &(*game).cub.bpp,
			&(*game).cub.line_lgh, &(*game).cub.endian);
	if (!(*game).cub.img || !(*game).cub.addr)
		(free_init_cub(game), exit(KO));
	cubed(game);
	return (OK);
}

// wall to draw from w during h
int	cubed(t_game *game)
{
	t_point	p;
	t_point	w;
	double	rad;
	double	h;
	int		i;
	double	r;

	p.x = (*game).map.pos_x;
	p.y = (*game).map.pos_y;
	i = -(*game).cub.img_w / 2;
	while (i < (*game).cub.img_w / 2)
	{
		rad = mod2pi((*game).map.alpha - atan(i / (*game).d_proj));
		r = ray(game, p, rad);
		h = TILE_SIZE * (*game).cub.img_h / (r * cos(atan(i / (*game).d_proj)));
		// wall
		w.y = (*game).cub.img_h / 2 - h / 2;
		w.x = i + (*game).cub.img_w / 2;
		draw_tex_line(*game, rad, h, w);
		(*game).lag = (t_point){0};
		(*game).side = 0;
		// ceil
		w.y = 0;
		draw_star_line(&(*game).cub, w, (*game).cub.img_h / 2 - h / 2,
			(*game).c_ceil);
		// floor
		w.y = (*game).cub.img_h / 2 + h / 2 - 1;
		draw_v_line(&(*game).cub, w, (*game).cub.img_h / 2 - h / 2,
			(*game).c_floor);
		i = i + 1;
	}
	minimap(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->cub.img, 0, 0);
	return (OK);
}

t_img	compass(t_game game, double rad)
{
	if (ray_on_door(game) == 1 && game.door_status != 2)
		return (game.d0);
	// return (*(game.sprite1)); // game.img_N;
	if ((game).horv == 'h')
	{
		if (0 <= rad && rad <= PI)
		{
			if (game.side == 'D')
				return (game.s0);
			else
				return (*(game.sprite1)); // game.img_N;
		}
		else
		{
			if (game.side == 'D')
				return (game.s0);
			else
				return (game.img_N); // return (game.img_S);
		}
	}
	else
	{
		if (-PI / 2 <= rad && rad <= PI / 2)
		{
			if (game.side == 'D')
				return (game.s0);
			else
				return (*(game.sprite2)); // return (game.img_E);
		}
		else
		{
			if (game.side == 'D')
				return (game.s0);
			else
				return (game.img_W);
		}
	}
}
//|| game.door_status == 1 || game.door_status == 3)) // pas ouvert
// return (printf("bouuuuuu  = %d\n", game.door_status), game.img_W);

void	draw_tex_line(t_game game, double rad, int h, t_point w)
{
	t_img	tex;
	double	j;
	int		k;
	double	absc;

	tex = compass(game, rad);
	// fit en largeur
	if (game.horv == 'h' && (0 <= rad && rad <= PI))
		absc = game.m.x - game.lag.x;
	else if (game.horv == 'h')
		absc = game.map.cols * TILE_SIZE - game.m.x + game.lag.x;
	else if (game.horv == 'v' && (-PI / 2 <= rad && rad <= PI / 2))
		absc = game.m.y - game.lag.y;
	else // else if (game.horv == 'v')
		absc = game.map.rows * TILE_SIZE - game.m.y + game.lag.y;
	// absc = (int)game.m.x % TILE_SIZE;
	// absc = absc * ((double)tex.img_w / TILE_SIZE);
	absc = (int)absc % TILE_SIZE + absc - (int)absc;
	absc = (absc / TILE_SIZE) * (tex.img_w);
	// absc = absc - game.lag*(tex.img_w) ;
	// fit en hauteur
	k = 0;
	while (k < h)
	{
		j = k * ((double)tex.img_h / h);
		put_pixel_img(&game.cub, (int)w.x, (int)w.y + k, get_pix(tex, (int)j,
				(int)absc));
		k++;
	}
}

// Get the color of the pixel, i.e. the pixel, from a texture, hit on M
// at z altitude on the abscise M.x (case h) or M.y (case v)
unsigned int	get_pix(t_img tex, int z, int absc)
{
	unsigned int color;

	// unsigned int	i;
	/*******************security to be checked ********* */
	// i = z * tex.line_lgh + absc * sizeof(int);
	// absc < tex.img_w && z < tex.img_h
	// if (tex.addr + (z * tex.line_lgh + absc * sizeof(int)) != NULL)
	if (absc < tex.img_w && z < tex.img_h)
		color = *(unsigned int *)(tex.addr + (z * tex.line_lgh + absc
					* sizeof(int)));
	else
		color = 0;
	return (color);
}