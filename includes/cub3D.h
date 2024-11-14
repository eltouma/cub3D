/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 01:15:59 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/03 02:34:44 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../includes/get_next_line.h"
# include "../includes/structures.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <sys/types.h>

# define OK 0
# define KO 1

# define WIN_W 1920
# define WIN_H 1080
# define TS 12
# define STEP 6
# define STEP_ALPHA 4
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
# define KEY_Q 113
# define KEY_ESC 65307

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

// mlx errors
# define EMCIM "Error\nCan't initialize the MLX.\n"
# define EMMTB "Error\nThe map is too big for the screen.\n"
# define EMCGW "Error\nMLX can't generate the window.\n"
# define ELOAD "Error\nMLX can't load whole images.\n"

// main.c
// init.c
void			init(t_game *game);
int				check_input(int argc, char **argv);
int				check_file_ext(char *fullname, char *ext);

// parsing_data.c
int				get_data(char *argv1, t_data *data);
int				parse_data_line(char *str, t_data *data);

// parsing_data_utils.c
int				check_no(char *str, t_data *data);
int				check_so(char *str, t_data *data);
int				check_we(char *str, t_data *data);
int				check_ea(char *str, t_data *data);

// parsing_utils1.c
void			get_path(char *str, t_data *data, char card);
int				fill_ceil(char *str, t_data *data);
int				fill_floor(char *str, t_data *data);

// parsing_utils2.c
int				count_comma(char *str);
int				is_space(char c);
int				is_number(char c);

// parsing_scene.c
int				is_scene(char *argv1);
int				is_data_line(char *str);
int				is_empty(char *str);
int				is_map_line(char *str);
int				is_map_char(char c);
// parsing_scene.c
int				is_map_last(char *argv1, int is_map, int end_map, int fd);
// parsing_path.c
int				check_path(t_data *data);
int				is_valid_path(char **path);
int				is_dup_path(t_data *data);

// parsing_map.c
int				get_map(char *argv1, t_map *map);
int				is_map_closed(t_map map);
int				is_line_closed(char *str);
int				handle_player(t_map *map, int count);
void			update_player_map(t_map *map, char player, int pos_x,
					int pos_y);

// parsing_map_utils.c
int				get_dim(char *argv1, t_map *map);
char			**create_map(char *argv1, t_map *map);
char			**fill_map(char **newmap, t_map *map, int fd);
char			**transpose(char **mat, size_t rows, size_t cols);

// mlx.c
int				init_mlx(t_game *game);
void			get_screen_size(t_game *game);
void			set_img_size(t_game *game);
void			set_colors(t_game *game);
void			start_game(t_game *game);
void			xpm_loader(t_game *game);

// load.c
void			load_all_xpm(t_game *game);
void			load_tab_xpm(t_game *game);
int				check_tab_xpm(t_game *game);
void			destroy_tab_xpm(t_game *game);
void			destroy_all_xpm(t_game *game);
void			get_all_addr(t_game *game);

// events.c
int				handle_close(t_game *game);
int				handle_key(int key_code, t_game *game);
void			init_events(t_game *game);
int				is_wall(t_map map, t_point p);
void			move_alpha(t_game *game, int deg);
void			move_dir(t_game *game, int step);
void			move_dir2(t_game *game, int step);
double			mod2pi(double rad);

// split.c
char			**ft_split(char *str, char c);

// tools1.c
void			*ft_memset(void *s, int c, unsigned int n);
char			*ft_substr(char *str, unsigned int start, size_t lenght);
int				ft_atoi_cub(char *str);

// tools2.c
int				ft_strcmp(char *s1, char *s2);
char			*ft_strdup(char *str);
unsigned int	get_pix(t_img tex, int z, int absc);

// free.c
void			free_data(t_data *data);
void			*free_tab(char **tab);
void			double_free(char **tab);
void			free_newtab(char **tab, int j);
void			free_game(t_game *game);
void			free_cub(t_game *game);

// errors.c
void			putstr_fd(char *s, int fd);
void			err_msg(char *str);

// ray_cast.c
void			init_maze(t_game *game);
double			ray(t_map map, t_point p, double rad, t_game *game);
void			init_cub(t_game *game);
void			cubed(t_game *game);
void			draw_tex_line(t_game game, double rad, int h, t_point w);
t_img			compass(t_game game, double rad);

// ray_inter.c
double			ray_inter_h(t_map map, t_point p, double rad, t_point *m);
double			ray_inter_h2(t_map map, t_point p, double rad, t_point *m);
double			ray_inter_v(t_map map, t_point p, double rad, t_point *m);
double			ray_inter_v2(t_map map, t_point p, double rad, t_point *m);
// ray_inter_utils.c
void			check_dy_h(int dy, int count, double rad, double *r);
void			check_dx_v(int dx, int count, double rad, double *r);
int				is_outside_map(t_map map, t_point m);

// draw_utils.c
void			put_pixel_img(t_img *img, int x, int y, int color);
void			draw_line(t_img *img, t_point a, t_point b, int color);
void			draw_h_line(t_img *img, t_point p, int lenght, int color);
void			draw_v_line(t_img *img, t_point p, int lenght, int color);
void			draw_tile(t_img *img, t_point p, int lenght, int color);
void			grid_line(t_img *img, t_map map, int tile_w);
void			grid(t_img *img, t_map map, int tile_w);
void			draw_angle_line(t_img *img, t_point p, double rad, double r);
void			draw_point(t_img *img, t_point p, int color);
int				create_trgb(int t, int r, int g, int b);

#endif
