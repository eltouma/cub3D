# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/12 14:18:13 by eltouma           #+#    #+#              #
#    Updated: 2024/10/05 21:09:16 by caguillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = cub3D_bonus

CC = cc -Wall -Wextra -Werror -g3
MAKEFLAGS += --no-print-directory

GREEN := \e[32m
RESET :=\e[0m

MLX_DIR		=	./minilibx-linux
MLX			= $(MLX_DIR)/libmlx.a
MLXLIB		= 	$(MLX) -lXext -lX11 -lm -lrt

INCS_DIR	=	-Iincludes -Iminilibx-linux
INCS_DIR_BONUS	=	-Iincludes_bonus -Iminilibx-linux

SRCS_PATH = $(shell find srcs -type d)
BONUS_PATH = $(shell find bonus -type d)

SRCS	= parsing_scene.c parsing_data.c parsing_utils1.c parsing_utils2.c parsing_path.c parsing_map.c \
	parsing_map_utils.c split.c tools1.c tools2.c free.c get_next_line.c get_next_line_utils.c errors.c \
	mlx.c load.c events.c draw_line.c draw_line_utils.c draw_utils.c grid.c ray_inter.c ray_cast.c \
	init.c move.c handle_walls.c destroy_xpm.c parsing_scene_utils.c free_game.c \
	parsing_data_utils.c ray_inter_utils.c main.c

BONUS	= parsing_scene_bonus.c parsing_data_bonus.c parsing_data_utils1_bonus.c parsing_data_utils2_bonus.c \
	parsing_utils1_bonus.c parsing_utils2_bonus.c parsing_path_bonus.c parsing_map_bonus.c parsing_map_utils_bonus.c \
	split_bonus.c tools1_bonus.c tools2_bonus.c free1_bonus.c get_next_line.c get_next_line_utils.c free2_bonus.c \
	mlx_bonus.c load_bonus.c events1_bonus.c ray_cast_bonus.c sprite_bonus.c side_doors_bonus.c \
	draw_utils_bonus.c draw_grid_bonus.c draw_bonus.c draw_line_bonus.c \
	ray_inter_h_bonus.c ray_inter_h2_bonus.c ray_inter_v_bonus.c ray_inter_v2_bonus.c ray_inter_utils_bonus.c \
	minimap_bonus.c init_bonus.c doors1_bonus.c doors2_bonus.c events2_bonus.c parsing_doors_bonus.c main_bonus.c

vpath %.c $(foreach dir, $(SRCS_PATH), $(dir):)
vpath %.c $(foreach dir, $(BONUS_PATH), $(dir):)

OBJS_PATH = objs/

OBJS = $(addprefix $(OBJS_PATH), $(SRCS:%.c=%.o))
OBJS_BONUS = $(addprefix $(OBJS_PATH), $(BONUS:%.c=%.o))

all: $(NAME)

$(OBJS_PATH)%.o: %.c
	@mkdir -p $(OBJS_PATH)
	$(CC) -c $< -o $@

$(NAME): $(OBJS)
	make --no-print-directory -C "./minilibx-linux"
	make -C $(MLX_DIR)
	$(CC) $(OBJS) -Inc $(MLXLIB) -Inc $(INCDS_DIR) -lreadline -o $(NAME)
	@echo "\nCompilation cub3D: $(GREEN)success$(RESET)\n"

$(NAME_BONUS): $(OBJS_BONUS)
	make --no-print-directory -C "./minilibx-linux"
	make -C $(MLX_DIR)
	$(CC) $(OBJS_BONUS) -Inc $(MLXLIB) -Inc $(INCDS_DIR_BONUS) -lreadline -o $(NAME_BONUS)
#	@echo "\nCompilation cub3D bonus: $(GREEN)success$(RESET)\n"

bonus: $(NAME_BONUS)

clean:
	make -C $(MLX_DIR) clean
	/bin/rm -rf $(OBJS) $(OBJS_BONUS)
	@echo "\nCub3D removed: $(GREEN)success$(RESET)\n"

fclean:	clean
	/bin/rm -rf ${NAME} $(NAME_BONUS)

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus
