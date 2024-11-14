/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:11:07 by eltouma           #+#    #+#             */
/*   Updated: 2024/10/05 22:43:37 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_BONUS_H
# define STRUCTURES_BONUS_H

# define IMG_NBR 10

// settings
typedef struct s_data
{
	char				*north;
	char				*south;
	char				*west;
	char				*east;
	char				*door;
	char				*side;
	char				*s0;
	char				*s1;
	char				*s2;
	char				*s3;
	int					ceil[3];
	int					floor[3];
	unsigned char		ceil_dup:1;
	unsigned char		floor_dup:1;
}						t_data;

// status = 0 closed / 1 opening / 2 opened / 3 closing
typedef struct s_door
{
	int					i;
	int					j;
	int					status;

}						t_door;

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
	int					i_mini;
	int					j_mini;
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

typedef struct timespec	t_nsec;

// cc = color_ceil
// cf = color_floor
// d_proj = distance from player to the projection plan
// horv = if the ray hit a vertical line or a horizontal line
// m = point where a ray hit the wall
// minimap
// sprite
// doors
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
	t_img				img_o;
	t_img				img_e;
	void				*tab_img[IMG_NBR];
	t_img				cub;
	double				d_proj;
	int					cc;
	int					cf;
	char				horv;
	t_point				m;
	int					mini_maxi;
	t_nsec				t0;
	int					frame;
	t_img				*sprite1;
	t_img				*sprite2;
	t_img				s0;
	t_img				s1;
	t_img				s2;
	t_img				s3;
	t_img				df;
	t_img				ds;
	int					nb_doors;
	t_door				*doors;
	int					door_idx;
	t_nsec				t_door;
	t_nsec				t1;
	int					door_status;
	t_point				lag;
}						t_game;

#endif
