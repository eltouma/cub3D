/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 01:19:48 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/02 16:20:11 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

int	main(int argc, char **argv)
{
	t_game	game;

	init(&game);
	if (check_input(argc, argv) == KO)
		return (KO);
	if (is_scene(argv[1]) == 0)
		return (KO);
	if (is_map_last(argv[1], 0, 0, 0) == 0)
		return (KO);
	if (get_data(argv[1], &game.data) == KO)
		return (KO);
	if (check_path(&game.data) == KO)
		return (KO);
	if (get_map(argv[1], &game.map) == KO)
		return (free_data(&game.data), KO);
	if (check_doors(&game) == KO)
		return (KO);
	if (init_mlx(&game) == KO)
		return (free_game(&game), KO);
	return (OK);
}
// data free'd before in KO's
// data free'd before in KO's
// only map free'd before in KO's
// so need to free data here
// mlx free'd before in KO's
