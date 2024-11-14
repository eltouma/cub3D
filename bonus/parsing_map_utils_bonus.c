/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:43:49 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/26 01:23:26 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

static void	fill_map_tab(char **tab, char *line, size_t *j, size_t i);

// -1 to not take '\n'
// printf("rows %ld\n", (*map).rows);
// printf("cols %ld\n", (*map).cols);
int	get_dim(char *argv1, t_map *map)
{
	char	*str;
	int		fd;

	fd = open(argv1, O_RDONLY);
	if (fd < 0)
		return (perror("cub3D"), KO);
	str = get_next_line(fd);
	while (str)
	{
		if (!str)
			break ;
		if (is_map_line(str) == 1)
		{
			(*map).rows++;
			if ((*map).cols < ft_strlen(str) - 1)
				(*map).cols = ft_strlen(str) - 1;
		}
		free(str);
		str = get_next_line(fd);
	}
	if (close(fd) < 0)
		return (perror("cub3D"), KO);
	return (OK);
}

// build the map as a matrice (rows + 1, cols + 1)
char	**create_map(char *argv1, t_map *map)
{
	char	**tab;
	int		fd;

	fd = open(argv1, O_RDONLY);
	if (fd < 0)
		return (perror("cub3D"), NULL);
	tab = ft_calloc(sizeof(char *), ((*map).rows + 1));
	if (!tab)
		return (perror("cub3D"), close(fd), NULL);
	return (fill_map(tab, map, fd));
}

static void	fill_map_tab(char **tab, char *line, size_t *j, size_t i)
{
	if (*j < ft_strlen(line) && line[*j] && line[*j] != '\n')
		tab[i][*j] = line[*j];
	else
		tab[i][*j] = ' ';
	*j = *j + 1;
}

// fill row with the line, without '\n', and complete with 32 = ' '
// printf("%s\n", tab[i]);
// printf("i = %ld\n", i);
char	**fill_map(char **tab, t_map *map, int fd)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line) == 1)
		{
			tab[i] = malloc(sizeof(char) * ((*map).cols + 1));
			if (!tab[i])
				return (perror("cub3D"), free_newtab(tab, i), close(fd), NULL);
			j = 0;
			while (j < (*map).cols)
				fill_map_tab(tab, line, &j, i);
			tab[i][j] = '\0';
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (tab[(*map).rows] = NULL, close(fd), tab);
}

char	**transpose(char **mat, size_t rows, size_t cols)
{
	char	**tmat;
	size_t	i;
	size_t	j;

	tmat = ft_calloc(sizeof(char *), (cols + 1));
	if (!tmat)
		return (perror("cub3D"), NULL);
	j = 0;
	while (j < cols)
	{
		tmat[j] = malloc(sizeof(char) * (rows + 1));
		if (!tmat[j])
			return (perror("cub3D"), free_newtab(tmat, j), NULL);
		i = 0;
		while (i < rows && mat[i])
		{
			tmat[j][i] = mat[i][j];
			i++;
		}
		tmat[j][i] = 0;
		j++;
	}
	tmat[j] = NULL;
	return (tmat);
}

// // Function to check the map and transpose map
// void	print_mat(char **mat)
// {
// 	int	i;

// 	/**** tools = to be commented / take out ****/
// 	if (!mat)
// 		printf("matrice = null\n");
// 	i = 0;
// 	while (mat[i])
// 	{
// 		printf("[%s]\n", mat[i]);
// 		i++;
// 	}
// }
