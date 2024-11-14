/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 02:50:58 by caguillo          #+#    #+#             */
/*   Updated: 2024/09/12 05:16:15 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// avec le clavier
void	init_maze(t_game *game)
{
	t_point	p;
	double	rad;
	double	r;
	int		i;

	// char	horv;
	(*game).maze.img = mlx_new_image((*game).mlx, (*game).maze.img_w,
			(*game).maze.img_h);
	(*game).maze.addr = mlx_get_data_addr((*game).maze.img, &(*game).maze.bpp,
			&(*game).maze.line_lgh, &(*game).maze.endian);
	grid(&(*game).maze, (*game).map);
	p.x = (*game).map.pos_x;
	p.y = (*game).map.pos_y;
	i = -(*game).cub.img_w / 2; // -240
	while (i < (*game).cub.img_w / 2)
	{
		// rad = mod2pi((*game).map.alpha - i * FOV / 480);
		rad = mod2pi((*game).map.alpha - atan(i / (*game).d_proj));
		r = ray((*game).map, p, rad, game);
		draw_angle_line(&(*game).maze, p, rad, r);
		i++;
	}
	// r = ray_inter_v2((*game).map, p, rad);
	// r = ray((*game).map, p, rad);
	// draw_angle_line(&img, p, rad, r);
	mlx_put_image_to_window(game->mlx, game->mlx_winmaze, game->maze.img, 0, 0);
}

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
	// draw_angle_line(&img, p, rad, rv);
	// draw_angle_line(&img, p, rad, rh);
}

void	init_cub(t_game *game)
{
	t_point	p;
	t_point	w;
	double	rad;
	double	h;
	int		i;
	double	r;

	// int		color;
	// char	horv;
	(*game).cub.img = mlx_new_image((*game).mlx, (*game).cub.img_w,
			(*game).cub.img_h);
	(*game).cub.addr = mlx_get_data_addr((*game).cub.img, &(*game).cub.bpp,
			&(*game).cub.line_lgh, &(*game).cub.endian);
	p.x = (*game).map.pos_x;
	p.y = (*game).map.pos_y;
	i = -(*game).cub.img_w / 2;
	while (i < (*game).cub.img_w / 2) //<=479
	{
		rad = mod2pi((*game).map.alpha - atan(i / (*game).d_proj));
		r = ray((*game).map, p, rad, game);
		// if ((*game).horv == 'v')
		// 	color = 0xFFFFFFFF;
		// else
		// 	color = 0xFF808080;
		h = TILE_SIZE * (*game).cub.img_h / (r * cos(atan(i / (*game).d_proj)));
		if (h > (*game).cub.img_h)
			h = (*game).cub.img_h;
		// wall
		w.y = (*game).cub.img_h / 2 - h / 2;
		w.x = i + (*game).cub.img_w / 2;
		draw_tex_line(*game, rad, h, i);
		// draw_v_line(&(*game).cub, w, h, color);
		// ceil
		w.y = 0;
		draw_v_line(&(*game).cub, w, (*game).cub.img_h / 2 - h / 2,
			(*game).c_ceil);
		// floor
		w.y = (*game).cub.img_h / 2 + h / 2 - 1;
		draw_v_line(&(*game).cub, w, (*game).cub.img_h / 2 - h / 2,
			(*game).c_floor);
		i = i + 1;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->cub.img, 0, 0);
	// printf("%c\n", (*game).img_N.addr[0]);
	// printf("%p\n", (*game).img_N.addr);
	// printf("%c\n", (*game).img_W.addr[0]);
	// (*game).cub.addr = mlx_get_data_addr((*game).cub.img, &(*game).cub.bpp,
	// 		&(*game).cub.line_lgh, &(*game).cub.endian);
	// printf("cub = %ld\n", ft_strlen((*game).cub.addr));
}

// From a point W, go down (j increases), drawing pixel by pixel, till lenght h
// fit en hauteur
void	draw_tex_line(t_game game, double rad, int h, int i)
{
	t_point	w;
	t_img	tex;
	// double	ratio;

	int j; // src
	int k; // dest
	tex = compass(game, rad);
	/********************reprendre ici ******* */
	// printf("len tex = %ld\n", ft_strlen(tex.addr));
	/******************** ******* */
	// wall to draw from w during h
	w.y = game.cub.img_h / 2 - h / 2;
	w.x = i + game.cub.img_w / 2;
	// if (tex.img_h < h)
	// {
	// 	ratio = (double)h / tex.img_h;
	// 	j = 0;
	// 	k = 0;
	// 	while (k < h)
	// 	{
	// 		k = j * ratio;
	// 		// printf("k = %d\n", k);
	// 		while (k < (j + 1) * ratio)
	// 		{
	// 			put_pixel_img(&game.cub, (int)w.x, (int)w.y + k, get_pix(game,
	// 					j, tex));
	// 			k++;
	// 		}
	// 		j++;
	// 	}
	// }
	// else
	// {
		k = 0;
		while (k < h)
		{
			j = k * ((double)tex.img_h / h);
			put_pixel_img(&game.cub, (int)w.x, (int)w.y + k, get_pix(game, j,
					tex));
			k++;
		}
	// }
}
// printf("h = %d\n", h);
// printf("img_h = %d\n", tex.img_h);
// printf("ratio = %f\n", ratio);
// printf("start\n");

// Get the color of the pixel, i.e. the pixel, from a texture, hit on M
// at z altitude on the abscise M.x (case h) or M.y (case v)
// Fit en largeur
unsigned int	get_pix(t_game game, int z, t_img tex)
{
	int				absc;
	unsigned int	color;

	// first logical try (to fit)
	if (game.horv == 'h')
		absc = (int)game.m.x % TILE_SIZE;
	else
		absc = (int)(game.map.rows*TILE_SIZE - game.m.y )% TILE_SIZE;
	// duplicate
	// if (game.horv == 'h')
	// 	absc = (int)game.m.x % MIN(TILE_SIZE, tex.img_w);
	// else
	// 	absc = (int)game.m.y % MIN(TILE_SIZE, tex.img_w);	
	absc = absc * ((double)tex.img_w / TILE_SIZE);
	//
	// printf("rad = %f\n", rad);
	// printf("M.x = %f\n", game.m.x);
	// printf("M.y = %f\n", game.m.y);
	// printf("absc = %d\n", absc);
	// printf("absc = %d\tz = %d\n	", absc, z);
	//
	// if (z * tex.line_lgh + absc * sizeof(int) < ft_strlen(tex.addr))
	// {
	color = *(unsigned int *)(tex.addr + (z * tex.line_lgh + absc
				* sizeof(int)));
	// }
	// else
	// color = 0x00FFFFFF;
	return (color);
}

t_img	compass(t_game game, double rad)
{
	if (game.horv == 'h')
	{
		if (0 <= rad && rad <= PI)
			return (game.img_N);
		// return (printf("Nord\n"), game.img_N);
		else
			return (game.img_S);
		// return (printf("Sud\n"), game.img_S);
	}
	else
	{
		if (-PI / 2 <= rad && rad <= PI / 2)
			return (game.img_E);
		// return (printf("East\n"), game.img_E);
		else
			return (game.img_W);
		// return (printf("West\n"), game.img_W);
	}
}

// printf("d = %f\n", d );
// printf("atan %f\n", atan(i / d) * 360 / +(2 * PI));
// printf("rad %f\n", rad * 360 / (2 * PI));
// h =   48 * (*game).cub.img_h / r;
// printf("rad %f\n", rad * 360 / (2 * PI));
// printf("rad %f\n", rad );
// rad = rad - atan((double)(1) / (r * cos(rad)));
// rad = rad - (PI / 2) / 480;

//
// rad = PI / 4;
// i = 0;
// while (i < 480) //<=479
// {
// 	rad = rad - (double)(PI / 4) / 480;
// 	printf("rad %f\n", rad * 360 / (2 * PI));
// 	i++;
// }
// printf("1/ %f\n", (double)(1) / 480);

// void	draw_angle_line(t_raw *img, t_point p, double rad, double r)
// {
// 	t_point	m;

// 	printf("r = %f\n", r);
// 	printf("r sin dou = %f\n",  sin(rad));
// 	printf("r sin int = %d\n", (int)( sin(rad)));
// 	m.y = p.y - (int)(r * sin(rad));
// 	m.x = p.x + (int)(r * cos(rad));
// 	draw_line(img, p, m);
// 	printf("px %d py %d\n", (int)p.x, (int)p.y);
// 	printf("mx %d my %d\n", (int)m.x, (int)m.y);
// }

// t_point a, b;
// a.x = 30;
// a.y = 28;
// b.x = 150;
// b.y = 50;
// draw_line(&img, a, b);
// printf("ax %d ay %d\n", (int)a.x, (int)a.y);
// printf("bx %d by %d\n", (int)b.x, (int)b.y);
// double	test(double r)
// {
// 	r = r + 3;
// 	if (r > 12)
// 		return (r);
// 	else
// 		return (test(r));
// }

// avec le while
// void	init_img0(t_game *game)
// {
// 	t_img	img;
// 	t_point	p;
// 	double	rad;
// 	double	r;
// 	int		n;

// 	// double	rv;
// 	// double	rh;
// 	img.img = mlx_new_image((*game).mlx, MAP_W, MAP_H);
// 	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_lgh, &img.endian);
// 	grid(&img, (*game).map);
// 	rad = PI / 5; // 30 degre
// 	p.x = 240;
// 	p.y = 240;
// 	n = 1;
// 	while (n <= 1)
// 	{
// 		// rad = (PI)*n / 200;
// 		// if (rad >= -PI / 2 && rad <= PI / 2)
// 		// 	rv = ray_inter_v2((*game).map, p, rad);
// 		// else
// 		// 	rv = ray_inter_v((*game).map, p, rad);
// 		// if (rad >= 0)
// 		// 	rh = ray_inter_h((*game).map, p, rad);
// 		// else
// 		// 	rh = ray_inter_h2((*game).map, p, rad);
// 		// printf("ici 1\n");
// 		// draw_angle_line(&img, p, rad, rv);
// 		// draw_angle_line(&img, p, rad, rh);
// 		r = ray((*game).map, p, rad);
// 		draw_angle_line(&img, p, rad, r);
// 		n++;
// 	}
// 	mlx_put_image_to_window((*game).mlx, (*game).mlx_win, img.img, 0, 0);
// }
// // printf("r = %f\n", r);