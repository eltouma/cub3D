/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:11:07 by eltouma           #+#    #+#             */
/*   Updated: 2024/08/18 02:40:29 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum	e_state
{
	SETTING,
	MAP,
	END,
}	t_state;

typedef struct s_check_dup
{
	unsigned char	no:1;
	unsigned char	so:1;
	unsigned char	we:1;
	unsigned char	ea:1;
	unsigned char	f:1;
	unsigned char	c:1;
}	t_check_dup;

typedef struct s_scene
{
	t_check_dup	check_dup;
	t_state		state;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	int			ceil[3];
	int			floor[3];
}			t_scene;

typedef struct s_data
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	int			ceil[3];
	int			floor[3];
}			t_data;

typedef struct s_game
{
	t_scene	scene;
	t_data	data;
}			t_game;

#endif
