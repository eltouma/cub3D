/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 01:19:48 by caguillo          #+#    #+#             */
/*   Updated: 2024/08/18 00:30:35 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int argc, char **argv)
{
	t_game	game;

	init(&game); // initialiser les couleurs a -1 ?
	if (check_input(argc, argv) == KO)
		return (KO);
	if (is_scene(argv[1]) == 0)
		return (KO);
	if (is_map_last(argv[1]) == 0)
		return (KO);
	if (check_scene(argv, &game.scene) == KO) // free(&game.scene) ?
		return (KO);
	// free_scene(&game.scene);
	// if (count_rows(&game, argv[1]) == 0)
	// 	return (0);
	// game.map = create_map(game.rows, argv[1]);
	// if (!game.map)
	// 	return (0);
	// if (check_map(&game) == 0)
	// 	return (free_map(game.map, game.rows), 0);
	// if (init_mlx(&game) == 0)
	// 	return (free_map(game.map, game.rows), 0);
	return (OK);
}

void	init(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	ft_memset(&game->scene, 0, sizeof(t_scene));
	ft_memset(&game->scene.check_dup, 0, sizeof(t_check_dup));
	ft_memset(&game->scene.state, 0, sizeof(t_state));
	
}

// Ne pas accepter les tab dans la map --> pourquoi ?
int	check_scene(char **argv, t_scene *scene)
{
	char	*str;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (putstr_fd(EOPN, 2), KO);
	while (scene->state != END)
	{
		if (scene->state == SETTING)
		{
			while (!check_fields(&scene->check_dup))
			{
				str = get_next_line(fd);
				if (!str)
					return (free_scene(scene), close(fd), KO);
				if (parse_line(str, scene) == KO)
					return (free_scene(scene), free(str), close(fd), KO);
				printf("%s", str);
				free(str);
			}
			scene->state = MAP;
		}
		if (scene->state == MAP)
		{
			str = get_next_line(fd);
			// parse la map;
			if (!str)
				scene->state = END;
			else
				printf("%s", str);
			free(str);
		}
	}
	// getchar();
	if (close(fd) == -1)
		return (putstr_fd(EGAL, 2), free_scene(scene), KO);
	return (free_scene(scene), OK);
}

// slash_dot (exec) managed by open actually ?
int	check_input(int argc, char **argv)
{
	if (argc > 2)
		return (putstr_fd(ETMA, 2), KO);
	if (argc < 2)
		return (putstr_fd(EMIS, 2), KO);
	// if (check_slash_dot(argv[1]) == KO)
	// 	return (putstr_fd(ENAM, 2), KO);
	if (check_file_ext(argv[1], ".cub") == KO)
		return (putstr_fd(EEXT, 2), KO);
	return (OK);
}

int	check_file_ext(char *fullname, char *ext)
{
	int	n;
	int	k;
	int	i;

	k = ft_strlen(ext);
	n = ft_strlen(fullname);
	if (n <= k)
		return (KO);
	i = 0;
	while (i < k)
	{
		if (fullname[n - i - 1] != ext[k - i - 1])
			return (KO);
		i++;
	}
	return (OK);
}

// int	check_slash_dot(char *name)
// {
// 	int	i;

// 	i = 0;
// 	while (name[i])
// 	{
// 		if (name[i] == '/' && name[i + 1] == '.')
// 			return (KO);
// 		i += 1;
// 	}
// 	return (OK);
// }
