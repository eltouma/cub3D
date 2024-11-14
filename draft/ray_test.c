/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 02:50:58 by caguillo          #+#    #+#             */
/*   Updated: 2024/09/07 01:58:15 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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

// avec le clavier
void	init_maze(t_game *game)
{
	t_point	p;
	double	rad;
	double	r;
	int		i;
	char	horv;

	// t_img	img;
	(*game).maze.img_w = (*game).map.cols * TILE_SIZE;
	(*game).maze.img_h = (*game).map.rows * TILE_SIZE;
	(*game).maze.img = mlx_new_image((*game).mlx, (*game).maze.img_w,
			(*game).maze.img_h);
	(*game).maze.addr = mlx_get_data_addr((*game).maze.img, &(*game).maze.bpp,
			&(*game).maze.line_lgh, &(*game).maze.endian);
	grid(&(*game).maze, (*game).map);
	// rad = (PI) / 5;
	p.x = (*game).map.pos_x;
	p.y = (*game).map.pos_y;
	i = -240;
	while (i < 240)
	{
		rad = mod2pi((*game).map.alpha - i * FOV / 480);
		r = ray((*game).map, p, rad, &horv);
		draw_angle_line(&(*game).maze, p, rad, r);
		i++;
	}
	// r = ray_inter_v2((*game).map, p, rad);
	// r = ray((*game).map, p, rad);
	// draw_angle_line(&img, p, rad, r);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->maze.img, 0, 0);
}

// -PI <= rad <= PI
double	ray(t_map map, t_point p, double rad, char *horv)
{
	double	rh;
	double	rv;

	if (rad >= -PI / 2 && rad <= PI / 2)
		rv = ray_inter_v2(map, p, rad);
	else
		rv = ray_inter_v(map, p, rad);
	if (rad >= 0)
		rh = ray_inter_h(map, p, rad);
	else
		rh = ray_inter_h2(map, p, rad);
	if (rh < rv)
	{
		//*color = 0x0FF808080;
		*horv = 'h';
		return (rh);
	}
	else
	{
		*horv = 'v';
		// *color = 0x0FFFFFFFF;
		return (rv);
	}
	// printf("ici 1\n");
	// draw_angle_line(&img, p, rad, rv);
	// draw_angle_line(&img, p, rad, rh);
}

void	init_cub10(t_game *game)
{
	t_point	p;
	t_point	v;
	double	rad;
	double	h;
	int		i;
	char	horv;
	int		color;
	double	r;

	// double	r0;
	(*game).cub.img_w = 480;
	(*game).cub.img_h = 480;
	(*game).cub.img = mlx_new_image((*game).mlx, (*game).cub.img_w,
			(*game).cub.img_h);
	(*game).cub.addr = mlx_get_data_addr((*game).cub.img, &(*game).cub.bpp,
			&(*game).cub.line_lgh, &(*game).cub.endian);
	p.x = (*game).map.pos_x;
	p.y = (*game).map.pos_y;
	// r = ray((*game).map, p, (*game).map.alpha, &horv);
	rad = (PI / 4);
	i = -240;
	while (i < 240) //<=479
	{
		 rad = mod2pi((*game).map.alpha - atan2( i,  320));
		// rad = mod2pi((*game).map.alpha + rad);
		r = ray((*game).map, p, mod2pi((*game).map.alpha + rad), &horv);
		if (horv == 'v')
		{
			color = 0xFFFFFFFF;
			// h =   48 * (*game).cub.img_h / r;
			h = 48 * (*game).cub.img_h / (r * cos(rad));
			//	h =   48 * (*game).cub.img_h / (r * (cos( -(PI) / 4 + e)));
			if (h > (*game).cub.img_h)
				h = (*game).cub.img_h;
			// printf("hv%f\n", h);
		}
		else
		{
			color = 0xFF808080;
			// h =  48 * (*game).cub.img_h / r;
			h = 48 * (*game).cub.img_h / (r * cos(rad));
			// h =  48 * (*game).cub.img_h / (r * (cos( -(PI) / 4 + e)));
			if (h > (*game).cub.img_h)
				h = (*game).cub.img_h;
			// printf("hh%f\n", h);
		}
		v.y = (*game).cub.img_h / 2 - h / 2;
		v.x = i + 240;
		draw_v_line(&(*game).cub, v, h, color);
		i = i + 1;
		printf("rad %f\n", rad * 360 / (2 * PI));
		// printf("rad %f\n", rad );
		rad = rad - atan((double)(1)/(r * cos(rad)));
		// rad = rad - (PI / 2) / 480;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->cub.img, 528, 0);
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
}

void	init_cub5(t_game *game)
{
	t_point	p;
	t_point	v;
	double	rad;
	double	h;
	int		i;
	char	horv;
	int		color;
	double	r;

	// t_point	m;
	// t_point	n;
	// double	r0;
	(*game).cub.img_w = 480;
	(*game).cub.img_h = 480;
	(*game).cub.img = mlx_new_image((*game).mlx, (*game).cub.img_w,
			(*game).cub.img_h);
	(*game).cub.addr = mlx_get_data_addr((*game).cub.img, &(*game).cub.bpp,
			&(*game).cub.line_lgh, &(*game).cub.endian);
	//
	p.x = (*game).map.pos_x;
	p.y = (*game).map.pos_y;
	r = ray((*game).map, p, (*game).map.alpha, &horv);
	//
	rad = mod2pi((*game).map.alpha + (PI / 4));
	// m.x = p.x + (int)(r * cos(rad));
	// m.y = p.y - (int)(r * sin(rad));
	rad = mod2pi((*game).map.alpha - (PI / 4));
	// n.x = p.x + (int)(r * cos(rad));
	// n.y = p.y - (int)(r * sin(rad));
	i = -240;
	while (i < 240) //<=479
	{
		// rad = (PI)*i / (479 * 2) - (PI) / 4;
		rad = mod2pi((*game).map.alpha - (i * (PI / 2) / 480));
		// rad = mod2pi((*game).map.alpha - atan2( i,  320));
		r = ray((*game).map, p, rad, &horv);
		if (horv == 'v')
		{
			color = 0xFFFFFFFF;
			// h =   48 * (*game).cub.img_h / r;
			h = 48 * (*game).cub.img_h / (r * (cos(i * (PI / 2) / 480)));
			//	h =   48 * (*game).cub.img_h / (r * (cos( -(PI) / 4 + e)));
			if (h > (*game).cub.img_h)
				h = (*game).cub.img_h;
			printf("hv%f\n", h);
		}
		else
		{
			color = 0xFF808080;
			// h =  48 * (*game).cub.img_h / r;
			h = 48 * (*game).cub.img_h / (r * (cos(i * (PI / 2) / 480)));
			// h =  48 * (*game).cub.img_h / (r * (cos( -(PI) / 4 + e)));
			if (h > (*game).cub.img_h)
				h = (*game).cub.img_h;
			printf("hh%f\n", h);
		}
		// if (h > 48*(*game).cub.img_h)
		// 	h = 48*(*game).cub.img_h;
		v.y = (*game).cub.img_h / 2 - h / 2;
		v.x = i + 240;
		draw_v_line(&(*game).cub, v, h, color);
		i = i + 1;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->cub.img, 528, 0);
}

void	init_cub(t_game *game)
{
	t_point	p;
	double	rad;
	double	h;
	int		i;
	char	horv;
	char	side;
	int		color;
	double	r;
	t_quad	q;
	int		new;

	// t_point	m;
	// t_point	v;
	(*game).cub.img_w = 480;
	(*game).cub.img_h = 480;
	(*game).cub.img = mlx_new_image((*game).mlx, (*game).cub.img_w,
			(*game).cub.img_h);
	(*game).cub.addr = mlx_get_data_addr((*game).cub.img, &(*game).cub.bpp,
			&(*game).cub.line_lgh, &(*game).cub.endian);
	p.x = (*game).map.pos_x;
	p.y = (*game).map.pos_y;
	side = 0;
	new = 1;
	i = -240;
	while (i < 240) //<=479
	{
		rad = mod2pi((*game).map.alpha - (i * (PI / 2) / 480));
		r = ray((*game).map, p, rad, &horv);
		// m.x = p.x + (int)(r * cos(rad));
		// m.y = p.y - (int)(r * sin(rad));
		if (horv == 'v')
		{
			color = 0xFFFFFFFF;
			// h =   48 * (*game).cub.img_h / r;
			h = 48 * (*game).cub.img_h / (r * (cos(i * (PI / 2) / 480)));
			//	h =   48 * (*game).cub.img_h / (r * (cos( -(PI) / 4 + e)));
			// if (h > (*game).cub.img_h)
			// 	h = (*game).cub.img_h;
			printf("hv%f\n", h);
		}
		else
		{
			color = 0xFF808080;
			// h =  48 * (*game).cub.img_h / r;
			h = 48 * (*game).cub.img_h / (r * (cos(i * (PI / 2) / 480)));
			// h =  48 * (*game).cub.img_h / (r * (cos( -(PI) / 4 + e)));
			// if (h > (*game).cub.img_h)
			// 	h = (*game).cub.img_h;
			printf("hh%f\n", h);
		}
		if (side != horv)
		{
			side = horv;
			if (new == 1)
			{
				q.B.x = i + 240;
				// q.B.y = (*game).cub.img_h / 2 + h / 2;
				q.A.x = i + 240;
				// q.A.y = (*game).cub.img_h / 2 - h / 2;
				// q.B.x = 10;
				q.B.y = 100;
				// q.A.x = 10;
				q.A.y = 10;
				new = 0;
				draw_line(&(*game).cub, q.A, q.B, color);
			}
			else
			{
				q.C.x = i + 240 - 1;
				// q.C.y = (*game).cub.img_h / 2 + h / 2;
				q.D.x = i + 240 - 1;
				// q.D.y = (*game).cub.img_h / 2 - h / 2;
				// q.C.x = i + 240;
				q.C.y = 240;
				// q.D.x = i + 240;
				q.D.y = 10;
				draw_line(&(*game).cub, q.D, q.C, 0x00FF80FF);
				// draw_trapeze(&(*game).cub, q, color);
				new = 1;
				q.B.x = i + 240;
				// q.B.y = (*game).cub.img_h / 2 + h / 2;
				q.A.x = i + 240;
				// q.A.y = (*game).cub.img_h / 2 - h / 2;
				// q.B.x = 10;
				q.B.y = 100;
				// q.A.x = 10;
				q.A.y = 10;
				draw_line(&(*game).cub, q.B, q.A, 0x00FF8080);
			}
		}
		if (i == 239)
		{
			q.C.x = i + 240;
			q.C.y = 240;
			q.D.x = i + 240;
			q.D.y = 40;
			draw_line(&(*game).cub, q.D, q.C, color);
			// draw_trapeze(&(*game).cub, q, color);
		}
		// v.y = (*game).cub.img_h / 2 - h / 2;
		// v.x = i + 240;
		// draw_v_line(&(*game).cub, v, h, color);
		i = i + 1;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->cub.img, 528, 0);
}

void	init_cub0(t_game *game)
{
	t_point	p;
	t_point	v;
	double	rad;
	double	h;
	int		i;
	char	horv;
	int		color;
	double	r;

	// double	r0;
	(*game).cub.img_w = 480;
	(*game).cub.img_h = 480;
	(*game).cub.img = mlx_new_image((*game).mlx, (*game).cub.img_w,
			(*game).cub.img_h);
	(*game).cub.addr = mlx_get_data_addr((*game).cub.img, &(*game).cub.bpp,
			&(*game).cub.line_lgh, &(*game).cub.endian);
	p.x = (*game).map.pos_x;
	p.y = (*game).map.pos_y;
	r = ray((*game).map, p, (*game).map.alpha, &horv);
	i = -240;
	while (i < 240) //<=479
	{
		// rad = (PI)*i / (479 * 2) - (PI) / 4;
		rad = mod2pi((*game).map.alpha - (i * (PI / 2) / 480));
		// rad = mod2pi((*game).map.alpha - atan2( i,  320));
		r = ray((*game).map, p, rad, &horv);
		if (horv == 'v')
		{
			color = 0xFFFFFFFF;
			// h =   48 * (*game).cub.img_h / r;
			h = 48 * (*game).cub.img_h / (r * (cos(i * (PI / 2) / 480)));
			//	h =   48 * (*game).cub.img_h / (r * (cos( -(PI) / 4 + e)));
			if (h > (*game).cub.img_h)
				h = (*game).cub.img_h;
			printf("hv%f\n", h);
		}
		else
		{
			color = 0xFF808080;
			// h =  48 * (*game).cub.img_h / r;
			h = 48 * (*game).cub.img_h / (r * (cos(i * (PI / 2) / 480)));
			// h =  48 * (*game).cub.img_h / (r * (cos( -(PI) / 4 + e)));
			if (h > (*game).cub.img_h)
				h = (*game).cub.img_h;
			printf("hh%f\n", h);
		}
		// if (h > 48*(*game).cub.img_h)
		// 	h = 48*(*game).cub.img_h;
		v.y = (*game).cub.img_h / 2 - h / 2;
		v.x = i + 240;
		draw_v_line(&(*game).cub, v, h, color);
		i = i + 1;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->cub.img, 528, 0);
}

// avec le ecart de points
void	init_cub2(t_game *game)
{
	t_point	p;
	t_point	v;
	double	rad;
	double	h;
	int		i;
	char	horv;
	int		color;
	double	r;
	t_point	m1;
	t_point	m2;

	// int j = 0;
	(*game).cub.img_w = 480;
	(*game).cub.img_h = 480;
	(*game).cub.img = mlx_new_image((*game).mlx, (*game).cub.img_w,
			(*game).cub.img_h);
	(*game).cub.addr = mlx_get_data_addr((*game).cub.img, &(*game).cub.bpp,
			&(*game).cub.line_lgh, &(*game).cub.endian);
	p.x = (*game).map.pos_x;
	p.y = (*game).map.pos_y;
	i = -240;
	while (i < 240) //<=479
	{
		// rad = (PI)*i / (479 * 2) - (PI) / 4;
		rad = mod2pi((*game).map.alpha - ((i + 1) * (PI / 2) / 480));
		r = ray((*game).map, p, rad, &horv);
		m2.x = (*game).map.pos_x - r * sin(rad);
		m2.y = (*game).map.pos_y + r * cos(rad);
		rad = mod2pi((*game).map.alpha - (i * (PI / 2) / 480));
		r = ray((*game).map, p, rad, &horv);
		m1.x = (*game).map.pos_x - r * sin(rad);
		m1.y = (*game).map.pos_y + r * cos(rad);
		if (horv == 'v')
		{
			color = 0xFFFFFFFF;
			// h =   48 * (*game).cub.img_h / r;
			h = 48 * (*game).cub.img_h / (r * (cos(i * (PI / 2) / 480)));
			//	h =   48 * (*game).cub.img_h / (r * (cos( -(PI) / 4 + e)));
			if (h > (*game).cub.img_h)
				h = (*game).cub.img_h;
			printf("hv%f\n", h);
		}
		else
		{
			color = 0xFF808080;
			// h =  48 * (*game).cub.img_h / r;
			h = 48 * (*game).cub.img_h / (r * (cos(i * (PI / 2) / 480)));
			// h =  48 * (*game).cub.img_h / (r * (cos( -(PI) / 4 + e)));
			if (h > (*game).cub.img_h)
				h = (*game).cub.img_h;
			printf("hh%f\n", h);
		}
		// if (h > 48*(*game).cub.img_h)
		// 	h = 48*(*game).cub.img_h;
		// if ((int)m1.x == (int)m2.x)
		// 	printf(" m1.x= %d\n", (int)m1.x);
		if (abs((int)m1.x - (int)m2.x) >= 1 || abs((int)m1.y - (int)m2.y) >= 1)
		{
			v.y = (*game).cub.img_h / 2 - h / 2;
			v.x = i + 240;
			draw_v_line(&(*game).cub, v, h, color);
		}
		i = i + 1;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->cub.img, 528, 0);
}

// petit e
void	init_cub1(t_game *game)
{
	t_point	p;
	t_point	v;
	double	rad;
	double	h;
	int		i;
	char	horv;
	int		color;
	double	r;
	double	e;
	double	rad2;
	double	r2;

	// (*game).cub.img_w = (*game).map.cols * TILE_SIZE;
	// (*game).cub.img_h = (*game).map.rows * TILE_SIZE;
	(*game).cub.img_w = 480;
	(*game).cub.img_h = 480;
	(*game).cub.img = mlx_new_image((*game).mlx, (*game).cub.img_w,
			(*game).cub.img_h);
	(*game).cub.addr = mlx_get_data_addr((*game).cub.img, &(*game).cub.bpp,
			&(*game).cub.line_lgh, &(*game).cub.endian);
	p.x = (*game).map.pos_x;
	p.y = (*game).map.pos_y;
	e = 0;
	rad2 = mod2pi((*game).map.alpha - (PI / 4));
	i = -240;
	while (i < 240) //<=479
	{
		// rad = mod2pi((*game).map.alpha -i * FOV / 480);
		// printf("e = %f\n", e);
		// rad = mod2pi((*game).map.alpha - (PI) / 4 + e);
		printf("rad2 = %f\n", rad2);
		rad = rad2;
		r = ray((*game).map, p, rad, &horv);
		if (horv == 'v')
		{
			color = 0xFFFFFFFF;
			h = 48 * (*game).cub.img_h / (r * (cos(i * (PI / 2) / 480)));
			if (h > (*game).cub.img_h)
				h = (*game).cub.img_h;
			printf("hv%f\n", h);
		}
		else
		{
			color = 0xFF808080;
			// h =  48 * (*game).cub.img_h / r;
			h = 48 * (*game).cub.img_h / (r * (cos(i * (PI / 2) / 480)));
			// h =  48 * (*game).cub.img_h / (r * (cos( -(PI) / 4 + e)));
			if (h > (*game).cub.img_h)
				h = (*game).cub.img_h;
			printf("hh%f\n", h);
		}
		v.y = (*game).cub.img_h / 2 - h / 2;
		v.x = i + 240;
		draw_v_line(&(*game).cub, v, h, color);
		// v.x = 240 + i + 1;
		// draw_v_line(&(*game).cub, v, h, color);
		// v.x = 240 + i + 2;
		// draw_v_line(&(*game).cub, v, h, color);
		// v.x = 240 + i + 3;
		// draw_v_line(&(*game).cub, v, h, color);
		// v.x = 240 + i + 4;
		// draw_v_line(&(*game).cub, v, h, color);
		// v.x = 240 + i + 5;
		// draw_v_line(&(*game).cub, v, h, color);
		// v.x = 240 + i + 6;
		// draw_v_line(&(*game).cub, v, h, color);
		// v.x = 240 + i + 7;
		// draw_v_line(&(*game).cub, v, h, color);
		i = i + 1;
		rad2 = rad; // mod2pi(rad + e);
		r2 = ray((*game).map, p, rad2, &horv);
		e = 0;
		while (fabs(r * sin(rad) - r2 * sin(rad2)) < 1 && fabs(r * cos(rad) - r2
				* cos(rad2)) < 1)
		{
			e = e + 0.0001;
			rad2 = mod2pi(rad2 + e);
			r2 = ray((*game).map, p, rad2, &horv);
			printf("e = %f\n", e);
		}
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->cub.img, 528, 0);
}

void	init_cub_tuto(t_game *game)
{
	t_point	p;
	t_point	v;
	double	rad;
	double	h;
	int		i;
	char	horv;
	int		color;
	double	r;

	(*game).cub.img_w = 320;
	(*game).cub.img_h = 320;
	(*game).cub.img = mlx_new_image((*game).mlx, (*game).cub.img_w,
			(*game).cub.img_h);
	(*game).cub.addr = mlx_get_data_addr((*game).cub.img, &(*game).cub.bpp,
			&(*game).cub.line_lgh, &(*game).cub.endian);
	p.x = (*game).map.pos_x;
	p.y = (*game).map.pos_y;
	i = -160;
	while (i < 160) //<=479
	{
		// rad = (PI)*i / (479 * 2) - (PI) / 4;
		rad = mod2pi((*game).map.alpha - (i * (PI / 3) / 320));
		r = ray((*game).map, p, rad, &horv);
		if (horv == 'v')
		{
			color = 0xFFFFFFFF;
			// h =   48 * (*game).cub.img_h / r;
			h = 64 * (*game).cub.img_h / (r * (cos(i * (PI / 3) / 320)));
			//	h =   48 * (*game).cub.img_h / (r * (cos( -(PI) / 4 + e)));
			if (h > (*game).cub.img_h)
				h = (*game).cub.img_h;
			printf("hv%f\n", h);
		}
		else
		{
			color = 0xFF808080;
			// h =  48 * (*game).cub.img_h / r;
			h = 64 * (*game).cub.img_h / (r * (cos(i * (PI / 3) / 320)));
			// h =  48 * (*game).cub.img_h / (r * (cos( -(PI) / 4 + e)));
			if (h > (*game).cub.img_h)
				h = (*game).cub.img_h;
			printf("hh%f\n", h);
		}
		// if (h > 48*(*game).cub.img_h)
		// 	h = 48*(*game).cub.img_h;
		v.y = (*game).cub.img_h / 2 - h / 2;
		v.x = i + 160;
		draw_v_line(&(*game).cub, v, h, color);
		i = i + 4;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->cub.img, 528, 0);
}
/*
void	draw_angle_line(t_raw *img, t_point p, double rad, double r)
{
	t_point	m;

	printf("r = %f\n", r);
	printf("r sin dou = %f\n",  sin(rad));
	printf("r sin int = %d\n", (int)( sin(rad)));
	m.y = p.y - (int)(r * sin(rad));
	m.x = p.x + (int)(r * cos(rad));
	draw_line(img, p, m);
	printf("px %d py %d\n", (int)p.x, (int)p.y);
	printf("mx %d my %d\n", (int)m.x, (int)m.y);
}

// int is_hit_wall()
// {

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


*/
