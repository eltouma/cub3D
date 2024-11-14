/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:11:07 by eltouma           #+#    #+#             */
/*   Updated: 2024/10/03 02:07:12 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# define IMG_NBR 4

// settings
typedef struct s_data
{
	char				*north;
	char				*south;
	char				*west;
	char				*east;
	int					ceil[3];
	int					floor[3];
	unsigned char		ceil_dup:1;
	unsigned char		floor_dup:1;
}						t_data;

// alpha = l'angle du player
typedef struct s_map
{
	char				**tab;
	size_t				rows;
	size_t				cols;
	double				alpha;
	size_t				pos_x;
	size_t				pos_y;
	int					map_w;
	int					map_h;
}						t_map;

typedef struct s_point
{
	double				x;
	double				y;

}						t_point;

// unity is byte
// sizeof(int) = 4 bytes
// bits_per_pixel = 32 bits
// 1 pixel (TRGB) = 1 int = 4 bytes = 4 * 8 bits = 32 bits
// line_length = bytes of 1 row = width * 1 int = width * 4 bytes
typedef struct s_img
{
	void				*img;
	char				*addr;
	int					bpp;
	int					line_lgh;
	int					endian;
	int					img_w;
	int					img_h;
}						t_img;

// cc = color_ceil
// cf = color_floor
// d_proj = distance from player to the projection plan
// horv = if the ray hit a vertical line or a horizontal line
// m = point where a ray hit the wall
typedef struct s_game
{
	t_data				data;
	t_map				map;
	void				*mlx;
	void				*mlx_win;
	int					win_w;
	int					win_h;
	t_img				img_n;
	t_img				img_s;
	t_img				img_w;
	t_img				img_e;
	void				*tab_img[IMG_NBR];	
	t_img				cub;
	double				d_proj;
	int					cc;
	int					cf;
	char				horv;
	t_point				m;	
}						t_game;

#endif
