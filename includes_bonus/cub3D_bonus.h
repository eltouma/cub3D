/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 01:15:59 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/05 22:51:43 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../includes_bonus/get_next_line.h"
# include "../includes_bonus/structures_bonus.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <sys/types.h>
# include <time.h>

# define OK 0
# define KO 1

# define WIN_W 1920
# define WIN_H 1080
# define TS 12
# define STEP 3
# define STEP_ALPHA 4
# define SPEED_MOUSE 3
// Number of tiles show on the minimap
# define SIZE_MINI 10
// Door opening duration in ms
# define TD 1000

// # define D0_PATH "./images/test/door0.xpm"
// # define S0_PATH "./images/test/s0.xpm"
// # define S1_PATH "./images/test/s1.xpm"
// # define S2_PATH "./images/test/s2.xpm"
// # define S3_PATH "./images/test/s3.xpm"

# define PI 3.1415926536
# define FOV 1.5707963268

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define KEY_ESC 65307
# define KEY_M 109
# define KEY_SPACE 32

// parsing errors
# define ETMA "Error\nToo many arguments\n"
# define EMIS "Error\nMap file (.cub) is missing\n"
# define EEXT "Error\nA map should be a \".cub\" file\n"
# define ESEM "Error\nScene is empty\n"
# define ENOM "Error\nNo map in the scene\n"
# define EDUP "Error\nUnvalid map: duplicate setting\n"
# define ELAM "Error\nThe map should be the last element of the scene\n"
# define EUNS "Error\nUnvalid scene\n"
# define EUNC "Error\nUnvalid color\n"
# define EUNP "Error\nUnvalid path\n"
# define ECMI "Error\nColor missing\n"
# define EWRS "Error\nWrong setting\n"
# define EPMI "Error\nPath missing\n"
# define EWRP "Error\nWrong path\n"
# define EDPA "Error\nDuplicate path\n"
# define EUMC "Error\nUnvalid map: not closed\n"
# define EUPL "Error\nUnvalid player\n"
# define EUDR "Error\nUnvalid door\n"

// mlx errors
# define EMCIM "Error\nCan't initialize the MLX.\n"
# define EMCGW "Error\nMLX can't generate the window.\n"
# define ELOAD "Error\nMLX can't load whole images.\n"
# define EIIMG "Error\nMLX can't initialize the image.\n"

// main_bonus.c
// init_bonus.c
void			init(t_game *game);
int				check_input(int argc, char **argv);
int				check_file_ext(char *fullname, char *ext);
int				check_tab_xpm(t_game *game);

// parsing_data_bonus.c
int				get_data(char *argv1, t_data *data);
int				parse_data_line(char *str, t_data *data);
int				parse_data_line2(char *str, t_data *data, int i);
// parsing_data_utils_bonus.c
int				parse_data_line_no(char *str, t_data *data);
int				parse_data_line_so(char *str, t_data *data);
int				parse_data_line_we(char *str, t_data *data);
int				parse_data_line_ea(char *str, t_data *data);
int				parse_data_line_df(char *str, t_data *data);
// parsing_data_utils2_bonus.c
int				parse_data_line_ds(char *str, t_data *data);
int				parse_data_line_s0(char *str, t_data *data);
int				parse_data_line_s1(char *str, t_data *data);
int				parse_data_line_s2(char *str, t_data *data);
int				parse_data_line_s3(char *str, t_data *data);
// parsing_utils1_bonus.c
void			get_path(char *str, t_data *data, char card);
void			get_path2(char *str, t_data *data, char card, int i);
int				fill_ceil(char *str, t_data *data);
int				fill_floor(char *str, t_data *data);
// parsing_utils2_bonus.c
int				count_comma(char *str);
int				is_space(char c);
int				is_number(char c);
int				is_empty(char *str);
// parsing_scene_bonus.c
int				is_scene(char *argv1);
int				is_data_line(char *str);
int				is_map_last(char *argv1, int is_map, int end_map, int fd);
int				is_map_line(char *str);
int				is_map_char(char c);
// parsing_path_bonus.c
int				check_path(t_data *data);
int				is_valid_path(char **path);
int				is_dup_path(t_data *data);
// parsing_map_bonus.c
int				get_map(char *argv1, t_map *map);
int				is_map_closed(t_map map);
int				is_line_closed(char *str);
int				handle_player(t_map *map, int count);
void			update_player_map(t_map *map, char player, int pos_x,
					int pos_y);
// parsing_map_utils_bonus.c
int				get_dim(char *argv1, t_map *map);
char			**create_map(char *argv1, t_map *map);
char			**fill_map(char **newmap, t_map *map, int fd);
char			**transpose(char **mat, size_t rows, size_t cols);
void			print_mat(char **mat);

// mlx_bonus.c
int				init_mlx(t_game *game);
void			start_game(t_game *game);
void			xpm_loader(t_game *game);
void			get_screen_size(t_game *game);
void			set_colors(t_game *game);

// load_bonus.c
void			load_all_xpm(t_game *game);
void			load_tab_xpm(t_game *game);
void			destroy_tab_xpm(t_game *game);
void			destroy_all_xpm(t_game *game);
void			get_all_addr(t_game *game);

// events1_bonus.c
// events2_bonus.c
void			init_events(t_game *game);
int				handle_mouse(int x, int y, t_game *game);
int				handle_close(t_game *game);
int				handle_key(int key_code, t_game *game);
void			move_alpha(t_game *game, int deg);
void			move_dir(t_game *game, int step);
void			move_dir2(t_game *game, int step);
double			mod2pi(double rad);
int				is_wall(t_map map, t_point p);
int				is_corner(t_map map, t_point p);

// split_bonus.c
char			**ft_split(char *str, char c);
// tools1_bonus.c
void			*ft_memset(void *s, int c, unsigned int n);
char			*ft_substr(char *str, unsigned int start, size_t lenght);
int				ft_atoi_cub(char *str);
// tools2_bonus.c
int				ft_strcmp(char *s1, char *s2);
char			*ft_strdup(char *str);
int				max(int a, int b);
int				min(int a, int b);
unsigned int	get_pix(t_img tex, int z, int absc);

// free1_bonus.c
void			free_data(t_data *data);
void			free_game(t_game *game);
void			free_cub(t_game *game);
void			free_init_cub(t_game *game);

// free2_bonus.c
void			putstr_fd(char *s, int fd);
void			err_msg(char *str);
void			*free_tab(char **tab);
void			double_free(char **tab);
void			free_newtab(char **tab, int j);

// ray_cast_bonus.c
double			ray(t_game *game, t_point p, double rad);
int				init_cub(t_game *game);
int				cubed(t_game *game, double rad);
void			draw_tex_line(t_game game, double rad, int h, t_point w);
t_img			compass(t_game game, double rad);

// side_doors_bonus.c
int				is_side_door_h(double rad, double mx);
int				is_side_door_h2(double rad, double mx);
int				is_side_door_v(double rad, double my);
int				is_side_door_v2(double rad, double my);
int				is_side_door(t_game game, double rad);

// ray_inter_utils_bonus.c
int				is_outside_map(t_map map, t_point m);
void			check_dy_h(int dy, int count, double rad, double *r);
void			check_dy_h2(int dy, double rad, double *r);
void			check_dx_v(int dx, int count, double rad, double *r);
void			check_dx_v2(int dx, double rad, double *r);

// ray_inter_bonus.c (h h2 v v2)
double			ray_inter_h(t_game *game, t_point p, double rad, t_point *m);
double			ray_inter_h2(t_game *game, t_point p, double rad, t_point *m);
double			ray_inter_v(t_game *game, t_point p, double rad, t_point *m);
double			ray_inter_v2(t_game *game, t_point p, double rad, t_point *m);

// draw_utils_bonus.c
void			put_pixel_img(t_img *img, int x, int y, int color);
void			draw_line(t_img *img, t_point a, t_point b, int color);
void			draw_h_line(t_img *img, t_point p, int lenght, int color);
void			draw_v_line(t_img *img, t_point p, int lenght, int color);
void			draw_tile(t_img *img, t_point p, int lenght, int color);
void			grid_line(t_img *img, t_map map, int tile_w);
void			grid_line_mini(t_img *img, t_map map, int tile_w);
void			grid(t_img *img, t_map map, int tile_w);
void			get_mini_limit(t_map *map, int tile_w, t_point p);
void			grid_mini(t_img *img, t_map *map, int tile_w, t_point p);
void			draw_angle_line(t_img *img, t_point p, double rad, double r);
void			draw_point(t_img *img, t_point p, int color);
int				create_trgb(int t, int r, int g, int b);
int				rand_range(int min, int max);
void			get_player_tile(t_point p, int *i, int *j, int tile_w);
void			draw_s_line(t_img *img, t_point p, int lenght, int color);

// minimap_bonus.c
void			minimap(t_game *game);
void			maximap(t_game *game);

// sprite_bonus.c
int				anim_loop(t_game *game);
int				get_diff_ms(t_nsec nano, t_nsec t0);

// doors1_bonus.c
int				ray_on_door(t_game game);
int				get_door_idx(t_game *game, int j, int i);
int				get_door_status(t_game game, int j, int i);
double			rest(double r, int nbr);
// doors2_bonus.c
void			move_door(t_game *game);
int				is_front_door(t_game *game);
int				is_door_closed(t_game game, t_point p);
// parsing_doors.c
int				check_doors(t_game *game);
int				is_valid_door(t_map map, size_t j, size_t i);
int				get_doors(t_game *game);
void			fill_doors(t_game *game);

#endif
