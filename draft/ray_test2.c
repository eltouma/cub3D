/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_test2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 02:50:58 by caguillo          #+#    #+#             */
/*   Updated: 2024/08/30 01:56:09 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
/*
void	put_pixel_img(t_raw *raw, int x, int y, int color)
{
	char	*dst;

	dst = (*raw).addr + (y * (*raw).line_lgh + x * ((*raw).bpp / 8));
	*(unsigned int *)dst = color;
}

void	test(t_game *game)
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	ray_dir_x;
	double	ray_dir_y;
	int		hit;
	int		x;

	printf("%s\n", __func__);
	//	t_point	p;
	dir_x = -1;
	dir_y = 12;
	plane_x = 0;
	plane_y = 0.66;
	//	double	time = 0;
	//	double	old_time = 0;
	double camera_x;	// x-coordinate in camera space;
	double map_x;		// x-coordinate of the current square the ray is in
	double map_y;		// y-coordinate of the current square the ray is in
	double side_dist_x; 	// distance the ray has to travel from its start pos to the first x-side;
	double side_dist_y; 	// distance the ray has to travel from its start pos to the first y-side;
	double delta_dist_x;	// distance the ray has to travel to go from 1 x-side to the next x-side;
	double delta_dist_y;	// distance the ray has to travel to go from 1 y-side to the next y-side;
	int step_x;		// what direction to step in x-direction (+1 or -1);
	int step_y;		// what direction to step in y-direction (+1 or -1);
	int side;		// was NS or EW wall hit?
	double	perp_wall_dist; // the length of the ray. //the perpenducular distance: use the shortest dist from a point to a line. The point is where the wall was hit. The line is the camera plane.    
	int	line_height;
	int	draw_start;
	int	draw_end;
	x = 0;
//	game->map.pos_y = 22; 
//	game->map.pos_x = 12;
	//	p.x = game->map.pos_x;
	//	p.y = game->map.pos_y;
	printf("player: %c\tpos_x: %ld\tpos_y: %ld\t\n", game->map.player,
		game->map.pos_x, game->map.pos_y);
	while (1)
	{
		while (x < SCREEN_W)
		{
			hit = 0;
			camera_x = 2 * x / (double)SCREEN_W - 1;
			printf("camera_x %f\n", camera_x);
			ray_dir_x = dir_x + plane_x * camera_x;
			printf("ray_dir_x %f\n", ray_dir_x);
			ray_dir_y = dir_y + plane_y * camera_x;
			printf("ray_dir_y %f\n", ray_dir_y);
			map_x = game->map.pos_x;
			map_y = game->map.pos_y;
			//			map_x = p.x;
			//			map_y = p.y;
			printf("map_x: %f\tmap_y: %f\t\n", map_x, map_y);
			if (!ray_dir_x)
				delta_dist_x = 1e30; // 1 X 10^30;
			else
				delta_dist_x = fabs(1 / ray_dir_x);
			if (!ray_dir_y)
				delta_dist_y = 1e30;
			else
				delta_dist_y = fabs(1 / ray_dir_y);
			printf("delta_dist_x: %f\n", delta_dist_x);
			printf("delta_dist_y: %f\n", delta_dist_y);
			if (ray_dir_x < 0)
			{
				step_x = -1;
				side_dist_x = (game->map.pos_x - map_x) * delta_dist_x;
			}
			else
			{
				step_x = 1;
				side_dist_x = (game->map.pos_x + 1.0 - map_x) * delta_dist_x;
			}
			if (ray_dir_y < 0)
			{
				step_y = -1;
				side_dist_y = (game->map.pos_y - map_y) * delta_dist_y;
			}
			else
			{
				step_y = 1;
				side_dist_y = (game->map.pos_y + 1.0 - map_y) * delta_dist_y;
			}
			printf("step_x: %d\tside_dist_x: %f\n", step_x, side_dist_x);
			printf("step_y: %d\tside_dist_y: %f\n", step_y, side_dist_y);
			while (!hit)
			{
				if (side_dist_x < side_dist_y)
				{
					side_dist_x += delta_dist_x;
					map_x += step_x;
					side = 0;
				}
				else
				{
					side_dist_y += delta_dist_y;
					map_y += step_y;
					side = 1;
				}
				if (SCREEN_W > 0 && SCREEN_H > 0)
					hit = 1;
				printf("side = %d\n", side);
				if (!side)
				{
					perp_wall_dist = side_dist_x - delta_dist_x;
					printf("Dans le if: perp_wall_dist %f\n", perp_wall_dist);
				}
				else
				{
					perp_wall_dist = side_dist_y - delta_dist_y;
					printf("Dans le else: perp_wall_dist %f\n", perp_wall_dist);
				}
			}
			line_height = SCREEN_H / perp_wall_dist;
			printf("line_h %d\n", line_height);
			draw_start = -line_height / 2 + SCREEN_H / 2;
			printf("draw_start %d\n", draw_start);
			if (draw_start < 0)
				draw_start = 0;
			draw_end = line_height / 2 + SCREEN_H / 2;
			if (draw_end >= SCREEN_H)
				draw_end = SCREEN_H - 1;
			printf("drwa_end %d\n", draw_end);
			x += 1;
		}
		break ;
	}
}

void	init_img(t_game *game)
{
	t_raw	img;

	printf("%s\n", __func__);
	printf("player: %c\tpos_x: %ld\tpos_y: %ld\t\n", game->map.player,
		game->map.pos_x, game->map.pos_y);
	img.img = mlx_new_image((*game).mlx, SCREEN_W, SCREEN_H);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_lgh, &img.endian);
	mlx_put_image_to_window((*game).mlx, (*game).mlx_win, img.img, 0, 0);
	test(game);
}
<<<<<<< HEAD
* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 02:50:58 by caguillo          #+#    #+#             */
/*   Updated: 2024/08/27 06:12:06 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*

double	ray_inter_h(t_map map, t_point p, double rad, double r);
void	draw_angle_line(t_raw *img, t_point p, double rad, double r);

void	put_pixel_img(t_raw *raw, int x, int y, int color)
{
	char	*dst;

	dst = (*raw).addr + (y * (*raw).line_lgh + x * ((*raw).bpp / 8));
	*(unsigned int *)dst = color;
}

// Draw an horizontale line from the point P to P + length
// step = 1 pixel
void	draw_h_line(t_raw *img, t_point p, int lenght, int color)
{
	int	i;

	i = 0;
	while (i < lenght)
	{
		put_pixel_img(img, p.x + i, p.y, color);
		i++;
	}
}

void	draw_v_line(t_raw *img, t_point p, int lenght, int color)
{
	int	j;

	j = 0;
	while (j < lenght)
	{
		put_pixel_img(img, p.x, p.y + j, color);
		j++;
	}
}

void	draw_tile(t_raw *img, t_point p, int lenght, int color)
{
	int		j;
	t_point	m;

	j = 0;
	m.x = p.x;
	while (j < lenght)
	{
		m.y = p.y + j;
		draw_h_line(img, m, lenght, color);
		j++;
	}
}

void	grid_line(t_raw *img, t_map map)
{
	t_point	m;
	size_t	j;
	size_t	i;

	m.x = 0;
	j = 0;
	while (j <= map.rows)
	{
		m.y = j * TILE_SIZE;
		draw_h_line(img, m, map.cols * TILE_SIZE, 0xFF808080);
		j++;
	}
	m.y = 0;
	i = 0;
	while (i <= map.cols)
	{
		m.x = i * TILE_SIZE;
		draw_v_line(img, m, map.rows * TILE_SIZE, 0xFF808080);
		i++;
	}
}

void	grid(t_raw *img, t_map map)
{
	t_point	m;
	size_t	i;
	size_t	j;

	// print_mat(map.tab);
	j = 0;
	while (j < map.rows)
	{
		// printf("%s\n", map.tab[i]);
		m.y = j * TILE_SIZE;
		i = 0;
		while (i < map.cols)
		{
			m.x = i * TILE_SIZE;
			if (map.tab[j][i] == '1')
				draw_tile(img, m, TILE_SIZE, 0xFFFFFFFF);
			else
				draw_tile(img, m, TILE_SIZE, 0x00000000);
			i++;
		}
		j++;
	}
	grid_line(img, map);
}

void	init_img(t_game *game)
{
	t_raw	img;
	t_point	p;
	double	rad;
	double	r;

	img.img = mlx_new_image((*game).mlx, SCREEN_W, SCREEN_H);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_lgh, &img.endian);
	grid(&img, (*game).map);
	rad = 1.0472;
	p.x = 250;
	p.y = 250;
	r = ray_inter_h((*game).map, p, rad, 0);
	// printf("r = %f\n", r);
	draw_angle_line(&img, p, rad, r);
	mlx_put_image_to_window((*game).mlx, (*game).mlx_win, img.img, 0, 0);
}

void	draw_line(t_raw *img, t_point a, t_point b)
{
	t_point	m;
	double	d;

	m = a;
	if (a.x != b.x)
	{
		d = (double)(a.y - b.y) / (a.x - b.x);
		while (m.x != b.x)
		{
			put_pixel_img(img, (int)m.x, (int)m.y, 0xFFFFFFFF);
			m.x = m.x + (b.x - a.x) / abs(b.x - a.x);
			m.y = d * m.x + (a.y - d * a.x);
		}
	}
	else if (a.y != b.y)
	{
		while (m.y != b.y)
		{
			put_pixel_img(img, (int)m.x, (int)m.y, 0xFFFFFFFF);
			m.y = m.y + (b.y - a.y) / abs(b.y - a.y);
		}
	}
	put_pixel_img(img, (int)a.x, (int)a.y, 0x0FF00000);
	put_pixel_img(img, (int)b.x, (int)b.y, 0x0FF00000);
}

// 0 <= rad <= PI / 2, sin(rad) >=0
// p.x = i * TILE_SIZE + dx
// p.y = j * TILE_SIZE + dy
double	ray_inter_h(t_map map, t_point p, double rad, double r)
{
	double	d;
	t_point	m;
	int		dy;

	// int		dx;
	// dx = p.x % TILE_SIZE;
	// printf("dx = %d\n", dx);
	dy = p.y % TILE_SIZE;
	if (dy == 0)
	{
		r = r + TILE_SIZE / sin(rad);
		d = TILE_SIZE / tan(rad);
	}
	else
	{
		r = r + dy / sin(rad);
		d = dy / tan(rad);
	}
	printf("r = %f\n", r);
	printf("d = %f\n", d);
	m.x = p.x + d;
	m.y = p.y - dy;
	//
	// printf("i = %d\n", (p.x - dx) / TILE_SIZE);
	// printf("j = %d\n", (int)((p.y + d) / TILE_SIZE));
	// hit wall?
	// printf("map %d\n", map.tab[0][0]);
	// printf("map %d\n", map.tab[1][1]);
	// printf("map %d\n", map.tab[4][5]);
	if (map.tab[(p.y - dy) / TILE_SIZE][(int)((p.x + d) / TILE_SIZE)] == '1')
		return (printf("ici\n"), printf("r = %f\n", r), r);
	else
		return (ray_inter_h(map, m, rad, r));
}

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
