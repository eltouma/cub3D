/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 01:47:05 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/02 02:30:24 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	*ft_memset(void *s, int c, unsigned int n)
{
	unsigned char	*game;

	game = s;
	while (n > 0)
	{
		*(game + n - 1) = c;
		n -= 1;
	}
	return (game);
}

// size_t = portable (32/64) unsigned int, so same or bigger
// start = indice, length = longueur
// lenght = 0 => ""
char	*ft_substr(char *str, unsigned int start, size_t lenght)
{
	char			*sub;
	unsigned int	i;
	size_t			size;

	if (!str)
		return (NULL);
	if (start >= ft_strlen(str))
		size = 0;
	else if (start + lenght - 1 >= ft_strlen(str))
		size = ft_strlen(str) - start;
	else
		size = lenght;
	sub = malloc(sizeof(char) * (size + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < size && str[i + start])
	{
		sub[i] = str[i + start];
		i++;
	}
	sub[size] = '\0';
	return (sub);
}

// *** Not used yet ***
int	ft_atoi(char *str)
{
	int					i;
	int					sign;
	unsigned long long	nbr;

	if (!str)
		return (0);
	i = 0;
	sign = 1;
	nbr = 0;
	while (str[i] && is_space(str[i]) == 1)
		i++;
	while (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] && 48 <= str[i] && str[i] <= 57)
	{
		nbr = nbr * 10 + (str[i] - 48);
		i++;
	}
	return (sign * nbr);
}

int	check_str(char *str, int nbr, int i, int sign)
{
	while (str[i] && str[i] != '\n')
	{
		if (is_space(str[i]) == 0)
		{
			if (!(str[i] >= 48 && str[i] <= 57) || sign == -1 || nbr > 255)
				return (-1);
			if (nbr == -1)
				nbr = 0;
			nbr = nbr * 10 + str[i] - 48;
		}
		else
		{
			while (str[i] && str[i] != '\n')
			{
				if (is_space(str[i]) == 0)
					return (-1);
				i++;
			}
			return (nbr);
		}
		i++;
	}
	return (nbr);
}

// spaces, +++, --- accepted before
// letter etc anywhere refused, only digit, +/-, spaces
// as max color is 255, no need to take anything above an int > 255
// nbr init to -1 in case of no while done (and for that case: "+++++ ,")
int	ft_atoi_cub(char *str)
{
	int	i;
	int	sign;
	int	nbr;

	if (!str)
		return (-1);
	i = 0;
	sign = 1;
	nbr = -1;
	while (str[i] && is_space(str[i]) == 1)
		i++;
	while (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	return (check_str(str, nbr, i, sign));
}
