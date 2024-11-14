/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:15:28 by eltouma           #+#    #+#             */
/*   Updated: 2024/08/16 23:33:26 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_fields(t_check_dup *check_dup)
{
	if (check_dup->no == 1 && check_dup->so == 1
		&& check_dup->we == 1 && check_dup->ea == 1
		&& check_dup->c == 1 && check_dup->f == 1)
		return (1);
	return (0);
}

int	parse_line(char *str, t_scene *scene)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (putstr_fd(EGAL, 2), KO);
	if (str[i] == '\n')
		return (OK);
	// if (is_space_no_nl(str[i]))
	// 	return (KO);
	//return (free(str), KO);
	if (str[i])
	{
		if (str[i] == 'N' && str[i + 1] == 'O' && is_space_no_nl(str[i + 2]))
		{
			if (scene->check_dup.no == 1)
				return (putstr_fd(EDUP, 2), KO);
			scene->check_dup.no = 1;
			return (get_path(str, scene, 'N'), OK);
		}
		if (str[i] == 'S' && str[i + 1] == 'O' && is_space_no_nl(str[i + 2]))
		{
			if (scene->check_dup.so == 1)
				return (putstr_fd(EDUP, 2), KO);
			scene->check_dup.so = 1;
			return (get_path(str, scene, 'S'), OK);
		}
		if (str[i] == 'W' && str[i + 1] == 'E' && is_space_no_nl(str[i + 2]))
		{
			if (scene->check_dup.we == 1)
				return (putstr_fd(EDUP, 2), KO);
			scene->check_dup.we = 1;
			return (get_path(str, scene, 'W'), OK);
		}
		if (str[i] == 'E' && str[i + 1] == 'A' && is_space_no_nl(str[i + 2]))
		{
			if (scene->check_dup.ea == 1)
				return (putstr_fd(EDUP, 2), KO);
			scene->check_dup.ea = 1;
			return (get_path(str, scene, 'E'), OK);
		}
	}
	if (str[i + 1])
	{
		if (str[i] == 'F' && str[i + 1] == 32 && count_comma(str) == 2)
		{
			if (scene->check_dup.f == 1)
				return (putstr_fd(EDUP, 2), KO);
			scene->check_dup.f = 1;
			return (fill_color_fc(str, scene));
		}
		else if (str[i] == 'C' && str[i + 1] == 32 && count_comma(str) == 2)
		{
			if (scene->check_dup.c == 1)
				return (putstr_fd(EDUP, 2), KO);
			scene->check_dup.c = 1;
			return (fill_color_fc(str, scene));
			//	 return (fill_color_fc(str, scene), OK); // Dans tous es cas, la fonction return OK, donc on se fout du return de fill_color_fc() et si on a C i,220,100, ca ne renvoie pas d'erreur
		}
	}
	//	return (OK);
	return (KO); // Pb dans txt ou couleurs
}

int	count_comma(char *str)
{
	int	i;
	int	count;

	if (!str)
		return (0);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

// void	parse_line_path(char *str, t_scene *scene, int i)
// {
// }

// path malloc'ed --> to be free'd
void	get_path(char *str, t_scene *scene, char card)
{
	int	i;

	i = 3; // skip NO_
	while (is_space_no_nl(str[i]))
		i++;
	if (card == 'N')
		(*scene).north = ft_substr(str, i, ft_strlen(str));
	if (card == 'S')
		(*scene).south = ft_substr(str, i, ft_strlen(str));
	if (card == 'W')
		(*scene).west = ft_substr(str, i, ft_strlen(str));
	if (card == 'E')
		(*scene).east = ft_substr(str, i, ft_strlen(str));
}

// int	fill_color_ceil(char *str, t_scene *scene)
int	fill_color_fc(char *str, t_scene *scene)
{
	int		i;
	int		j;
	char	**nb;

	i = 0;
	j = 0;
	nb = ft_split(str + 2, ',');
	if (!nb)
		return (KO);
	while (nb[i])
	{
		if (ft_strlen(nb[i]) > 3 || i > 3)
			return (putstr_fd(EACH, 2), free_tab(nb), KO);
		(*scene).ceil[j] = ft_atoi_cub(nb[i]);
		(*scene).ceil[j] = ft_atoi_cub(nb[i]);
		if ((*scene).ceil[j] > 255 || (*scene).ceil[j] < 0)
			return (putstr_fd(EACH, 2), free_tab(nb), KO);
		i += 1;
		j += 1;
	}
//	for (int a = 0; nb[i]; a++)
//		dprintf(2, "nb %s\n", nb[i]);
	return (free_tab(nb), OK);
}

/*
   int	fill_color_fc(char *str, t_scene *scene)
   {
   int		i;
   int		j;
   int		start;
   char	*nbr;

   i = 2; // skip C_
   j = 0;

   dprintf(2, "str %s", str);
   while (j < 3)
   {
   start = i;
   while (str[i] && str[i] != ',') // pb : si on a C k,45,9
   {
   if (!is_number(str[i]))
   return (KO);
   i++;
   }
   nbr = ft_substr(str, start, i - start);
   dprintf(2, "nbr %s\n", nbr);
   if (!nbr || ft_strlen(nbr) > 3)
   return (free(nbr), KO);
   (*scene).ceil[j] = ft_atoi(nbr);
   free(nbr);
   j++;
   i++;
   }
   return (OK);
   }
 */

// int get_color(char *str) = atoi

int	is_space_no_nl(char c)
{
	if (c == 9 || (c >= 11 && c <= 12) || c == 32)
		return (1);
	return (0);
}

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	is_number(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
