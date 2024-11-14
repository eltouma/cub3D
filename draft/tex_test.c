/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 23:45:44 by caguillo          #+#    #+#             */
/*   Updated: 2024/09/11 21:02:16 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

unsigned int	get_color(t_img tex, int i, int j);

void	init_tex(t_game *game)
{
	int	i;
	int	j;
	int	k;
	int	l;

	(*game).tex.img_w = (*game).img_N.img_w * 2;
	(*game).tex.img_h = (*game).img_N.img_h * 2;
	// printf("%d\n",(*game).tex.img_w);
	// printf("%d\n",(*game).tex.img_h);
	(*game).mlx_wintex = mlx_new_window((*game).mlx, (*game).tex.img_w,
			(*game).tex.img_h, "Tex");
	(*game).tex.img = mlx_new_image((*game).mlx, (*game).tex.img_w,
			(*game).tex.img_h);
	(*game).tex.addr = mlx_get_data_addr((*game).tex.img, &(*game).tex.bpp,
			&(*game).tex.line_lgh, &(*game).tex.endian);
	j = 0;
	l = 0;
	while (j < (*game).img_N.img_h)
	{
		i = 0;
		k = 0;
		while (i < (*game).img_N.img_w)
		{
			put_pixel_img(&(*game).tex, k, l, get_color((*game).img_N, i, j));			
			put_pixel_img(&(*game).tex, k+1, l, get_color((*game).img_N, i, j));			
			put_pixel_img(&(*game).tex, k, l+1, get_color((*game).img_N, i, j));
			put_pixel_img(&(*game).tex, k+1, l+1, get_color((*game).img_N, i, j));
			k = k + 2;
			i++;
		}
		l = l + 2;
		j++;
	}
	printf("i = %d\n", i);
	printf("j = %d\n", j);
	printf("k = %d\n", k);
	printf("l = %d\n", l);
	mlx_put_image_to_window(game->mlx, game->mlx_wintex, game->tex.img, 0, 0);
}

// reduce by 2
void	init_tex2(t_game *game)
{
	int	i;
	int	j;
	int	k;
	int	l;

	(*game).tex.img_w = (*game).img_N.img_w / 2;
	(*game).tex.img_h = (*game).img_N.img_h / 2;
	// printf("%d\n",(*game).tex.img_w);
	// printf("%d\n",(*game).tex.img_h);
	(*game).mlx_wintex = mlx_new_window((*game).mlx, (*game).tex.img_w,
			(*game).tex.img_h, "Tex");
	(*game).tex.img = mlx_new_image((*game).mlx, (*game).tex.img_w,
			(*game).tex.img_h);
	(*game).tex.addr = mlx_get_data_addr((*game).tex.img, &(*game).tex.bpp,
			&(*game).tex.line_lgh, &(*game).tex.endian);
	j = 0;
	l = 0;
	while (j < (*game).img_N.img_h)
	{
		if (j % 2 == 0)
		{
			i = 0;
			k = 0;
			while (i < (*game).img_N.img_w)
			{
				if (i % 2 == 0)
				{
					put_pixel_img(&(*game).tex, k, l, get_color((*game).img_N,
							i, j));
					k++;
				}
				i++;
			}
			l++;
		}
		j++;
	}
	printf("i = %d\n", i);
	printf("j = %d\n", j);
	printf("k = %d\n", k);
	printf("l = %d\n", l);
	mlx_put_image_to_window(game->mlx, game->mlx_wintex, game->tex.img, 0, 0);
}

unsigned int	get_color(t_img tex, int i, int j)
{
	unsigned int	color;

	color = *(unsigned int *)(tex.addr + (j * tex.line_lgh + i * sizeof(int)));
	return (color);
}
