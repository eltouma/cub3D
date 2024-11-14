/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_inter_bonus copy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 02:29:27 by caguillo          #+#    #+#             */
/*   Updated: 2024/10/01 20:01:40 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"


// dx != 0 != TS
// if (dx == 0 || TILE_SIZE == dx)
// 		printf("zero!!!\n");
int is_side_door_h(double rad, double mx)
{
	double max;
	double min;
	double dx;
	
	dx = rest(mx, TILE_SIZE);	
	max = PI - atan((TILE_SIZE / 2) / dx);	
	min = atan( (TILE_SIZE /2) / (TILE_SIZE - dx));	
	if (min < rad && rad < max)
		return(0);
	return (1);	
}

int is_side_door_h2(double rad, double mx)
{
	double max;
	double min;
	double dx;
	
	dx = rest(mx, TILE_SIZE);
	max = atan( (TILE_SIZE /2) / (dx - TILE_SIZE));
	min = atan((TILE_SIZE / 2) / dx) - PI;	
	if (min < rad && rad < max)
		return(0);
	return (1);	
}

int is_side_door_v(double rad, double my)
{
	double max;
	double min;
	double dy;	
		
	dy = rest(my, TILE_SIZE);
	max = -PI + atan((TILE_SIZE - dy) / (TILE_SIZE /2));		
	min = PI - atan(dy / (TILE_SIZE /2));	
	if ((min < rad && rad < PI) || (-PI < rad && rad < max))	
		return(0);
	return (1);	
}

int is_side_door_v2(double rad, double my)
{
	double max;
	double min;
	double dy;
	
	dy = rest(my, TILE_SIZE);
	max = atan(dy / (TILE_SIZE / 2) );
	min = atan( (dy - TILE_SIZE) / (TILE_SIZE /2));
	if ( min < rad && rad < max)
		return(0);
	return (1);	
}

// 0 <= rad <= PI, sin(rad) >= 0
// p.x = i * TILE_SIZE + dx
// p.y = j * TILE_SIZE + dy
double	ray_inter_h(t_game *game, t_point p, double rad, t_point *m)
{
	double	d;
	int		dy;
	double	r;
	int		count;
	t_nsec t1;

	// t_point	m;
	if (sin(rad) <= 0)
		return (WIN_W * WIN_W);
	*m = p;
	d = 0;
	r = 0;
	count = 1;
	while (1)
	{
		//(*game).lag = 0;
		dy = (int)(*m).y % TILE_SIZE;
		if (dy == 0) // on est sur une h
		{
			r = r + TILE_SIZE / sin(rad);
			if (count == 1)
				r = 0;
		}
		else // depart si pas sur une h
			r = dy / sin(rad);
		d = r * cos(rad);
		(*m).x = p.x + d;
		(*m).y = ((int)p.y - (int)p.y % TILE_SIZE) - count * TILE_SIZE;
		count++;
		if (is_outside_map((*game).map, *m) == 1) // || is_corner(map, *m) == 1)
			return (r);                   // printf("break %f\n", r),
		// hit wall?
		if ((*game).map.tab[(int)(*m).y / TILE_SIZE][(int)((*m).x / TILE_SIZE)] == '1')
			return (r);
			
		// hit door?	
		if ((*game).map.tab[(int)(*m).y / TILE_SIZE][(int)((*m).x / TILE_SIZE)] == 'D' )
			
		{
		if ( is_side_door_h(rad, (*m).x) == 0)			
		{	// int j = (int)(*m).y / TILE_SIZE;
			// int i = (int)((*m).x / TILE_SIZE);
			// (*m).x = (*m).x + (TILE_SIZE / 2) / tan(rad);
			// (*m).y = (*m).y - (TILE_SIZE / 2);			
			// printf("rentre\n");
			if (tan(rad) == 0 )
				printf("zero h\n");
			if (cos(rad) == 0 )
				printf("zero cos h\n");	
			clock_gettime(CLOCK_MONOTONIC, &t1);			
			if (get_door_status(*game, (int)(*m).y / TILE_SIZE, (int)((*m).x / TILE_SIZE)) == 0) // closed
			// if (get_door_status(*game, j, i) == 0) // closed
			{				
				// printf("status 0\n");
				// if (tan(rad) != 0 )
				(*m).x = (*m).x + (TILE_SIZE / 2) / tan(rad);
				(*m).y = (*m).y - (TILE_SIZE / 2);				
				return (r + (TILE_SIZE /2 ) / sin(rad));	// attention ici sin(rad) !=0 protection au debut
			}
			else if (get_door_status(*game, (int)(*m).y / TILE_SIZE, (int)((*m).x / TILE_SIZE)) == 1) // opening
			// else if (get_door_status(*game, j, i) == 1) // opening
			{
				// printf("status 1\n");
				// if (tan(rad) != 0 )
				(*m).x = (*m).x + (TILE_SIZE / 2) / tan(rad);
				(*m).y = (*m).y - (TILE_SIZE / 2);				
				if (rest((*m).x, TILE_SIZE) > get_diff_ms(t1, (*game).t_door) * TILE_SIZE/1000) // arret
				{
					if ((get_diff_ms(t1, (*game).t_door) < 1000) )
						//&& ((*game).map.tab[(int)(*m).y / TILE_SIZE ][(int)((*m).x / TILE_SIZE) - 1] != '1'))
						(*game).lag.x = get_diff_ms(t1, (*game).t_door) * TILE_SIZE/1000;					
					else
						(*game).lag.x = 0;	
					return (r + (TILE_SIZE /2 ) / sin(rad));		
				}				
				else //ca passe
				{					
					//(*game).lag = 0;						
					(*m).x = (*m).x - (TILE_SIZE / 2) / tan(rad);
					(*m).y = (*m).y + (TILE_SIZE / 2);
				}
			}
			else if (get_door_status(*game, (int)(*m).y / TILE_SIZE, (int)((*m).x / TILE_SIZE)) == 3) // closing
			// else if (get_door_status(*game, j, i) == 3) // closing
			{
				// printf("status 3\n");
				(*m).x = (*m).x + (TILE_SIZE / 2) / tan(rad);
				(*m).y = (*m).y - (TILE_SIZE / 2);				
				if (rest((*m).x, TILE_SIZE) > TILE_SIZE - get_diff_ms(t1, (*game).t_door) * TILE_SIZE/1000)
				{
					if (get_diff_ms(t1, (*game).t_door) < 1000)
						(*game).lag.x = TILE_SIZE - get_diff_ms(t1, (*game).t_door) * TILE_SIZE/1000;
					else
						(*game).lag.x = 0;	
					return (r + (TILE_SIZE /2 ) / sin(rad));		
				}				
				else // 
				{					
					// (*game).lag = 0;
					(*m).x = (*m).x - (TILE_SIZE / 2) / tan(rad);
					(*m).y = (*m).y + (TILE_SIZE / 2);					
				}
			}
		
		}
		else	
			(*game).side = 'D';	
		}
	}
}
//printf("%f\n",(*game).lag);

// -PI < rad < 0, sin(rad) < 0
// p.x = i * TILE_SIZE + dx
// p.y = j * TILE_SIZE + dy
double	ray_inter_h2(t_game *game, t_point p, double rad, t_point *m)
{
	double	d;
	int		dy;
	double	r;
	int		count;
	t_nsec t1;

	// t_point	m;
	if (sin(rad) >= 0)
		return (WIN_W * WIN_W);
	*m = p;
	d = 0;
	r = 0;
	count = 1;
	while (1)
	{
		// (*game).lag = 0;
		dy = (int)(*m).y % TILE_SIZE;
		if (dy == 0) // on est sur une h
			r = r + TILE_SIZE / fabs(sin(rad));
		else // depart si pas sur une h
			r = (TILE_SIZE - dy) / fabs(sin(rad));
		d = r * cos(rad);
		(*m).x = p.x + d;
		(*m).y = ((int)p.y - (int)p.y % TILE_SIZE) + count * TILE_SIZE;
		count++;
		if (is_outside_map((*game).map, *m) == 1) // || is_corner(map, *m) == 1)
			return (r);                   // return (printf("break %f\n", r),r);
		// hit wall?
		if ((*game).map.tab[(int)(*m).y / TILE_SIZE][(int)((*m).x / TILE_SIZE)] == '1')
			return (r);
		if ((*game).map.tab[(int)(*m).y / TILE_SIZE][(int)((*m).x / TILE_SIZE)] == 'D' )
		
		
			//&& fabs((TILE_SIZE - rest((*m).x, TILE_SIZE))*tan(rad)) > TILE_SIZE/2 ) 
		{
		if( is_side_door_h2(rad, (*m).x) == 0)	
		{
			if (tan(rad) == 0 )
				printf("zero h2\n");
			clock_gettime(CLOCK_MONOTONIC, &t1);
			if (get_door_status(*game, (int)(*m).y / TILE_SIZE, (int)((*m).x / TILE_SIZE)) == 0) // closed
			{
				(*m).x = (*m).x - (TILE_SIZE / 2) / tan(rad);
				(*m).y = (*m).y + (TILE_SIZE / 2);
				return (r - (TILE_SIZE / 2) / sin(rad));
			}									
			else if (get_door_status(*game, (int)(*m).y / TILE_SIZE, (int)((*m).x / TILE_SIZE)) == 1) // opening
			{
				// if (tan(rad) != 0 )
					(*m).x = (*m).x - (TILE_SIZE / 2) / tan(rad);
				(*m).y = (*m).y + (TILE_SIZE / 2);	
				if (rest((*m).x, TILE_SIZE) > get_diff_ms(t1, (*game).t_door) * TILE_SIZE/1000)
				{
					if (get_diff_ms(t1, (*game).t_door) < 1000)
						(*game).lag.x = get_diff_ms(t1, (*game).t_door) * TILE_SIZE/1000;												
					else
						(*game).lag.x = 0;	
					return (r - (TILE_SIZE /2 ) / sin(rad));		
				}				
				else //ca passe
				{					
					// if (tan(rad) != 0 )
						(*m).x = (*m).x + (TILE_SIZE / 2) / tan(rad);
					(*m).y = (*m).y - (TILE_SIZE / 2);
				}
			}
			else if (get_door_status(*game, (int)(*m).y / TILE_SIZE, (int)((*m).x / TILE_SIZE)) == 3) // closing
			{
				// if (tan(rad) != 0 )
					(*m).x = (*m).x - (TILE_SIZE / 2) / tan(rad);
				(*m).y = (*m).y + (TILE_SIZE / 2);	
				if (rest((*m).x, TILE_SIZE) > TILE_SIZE -  get_diff_ms(t1, (*game).t_door) * TILE_SIZE/1000) // arret
				{
					 if (get_diff_ms(t1, (*game).t_door) < 1000)
						(*game).lag.x = TILE_SIZE - get_diff_ms(t1, (*game).t_door) * TILE_SIZE/1000;
					else
						(*game).lag.x = 0;		
					return (r - (TILE_SIZE /2 ) / sin(rad));		
				}				
				else // 
				{						
					// if (tan(rad) != 0 )
						(*m).x = (*m).x + (TILE_SIZE / 2) / tan(rad);
					(*m).y = (*m).y - (TILE_SIZE / 2);					
				}
			}
		}	
		else	
			(*game).side = 'D';		
		}
		
	}
}

// PI/2 < rad < PI, cos(rad) < 0
// -PI < rad < -PI/2, cos(rad) < 0
// p.x = i * TILE_SIZE + dx
// p.y = j * TILE_SIZE + dy
double	ray_inter_v(t_game *game, t_point p, double rad, t_point *m)
{
	double	d;
	int		dx;
	double	r;
	int		count;
	t_nsec t1;

	// t_point	m;
	if (cos(rad) >= 0)
		return (WIN_H * WIN_H);
	*m = p;
	d = 0;
	r = 0;
	count = 1;
	while (1)
	{
		// (*game).lag = 0;
		dx = (int)(*m).x % TILE_SIZE;
		if (dx == 0) // on est sur une h
		{
			r = r - TILE_SIZE / cos(rad);
			if (count == 1)
				r = 0;
		}
		else // depart si pas sur une h
			r = -dx / cos(rad);
		d = r * sin(rad);
		(*m).y = p.y - d;
		(*m).x = ((int)p.x - (int)p.x % TILE_SIZE) - count * TILE_SIZE;
		count++;
		if (is_outside_map((*game).map, *m) == 1) // || is_corner(map, *m) == 1)
			return (r);                   // printf("break %f\n", r),
		// hit wall?
		if ((*game).map.tab[(int)((*m).y / TILE_SIZE)][(int)(*m).x / TILE_SIZE] == '1')			
			return (r);			
		if ((*game).map.tab[(int)((*m).y / TILE_SIZE)][(int)(*m).x / TILE_SIZE] == 'D')			
		{
		if (is_side_door_v(rad, (*m).y) == 0)
		{
			if (tan(rad) == 0 )
				printf("zero v\n");
			if (cos(rad) == 0 )
				printf("zero cos v\n");	
			clock_gettime(CLOCK_MONOTONIC, &t1);			
			if (get_door_status(*game, (int)((*m).y / TILE_SIZE), (int)(*m).x / TILE_SIZE) == 0) // closed
			{			
				(*m).x = (*m).x - (TILE_SIZE / 2);				
				(*m).y = (*m).y - (TILE_SIZE / 2) * (-tan(rad));
				return (r - (TILE_SIZE / 2) / cos(rad));
			}						
			else if (get_door_status(*game, (int)((*m).y / TILE_SIZE), (int)(*m).x / TILE_SIZE) == 1)
			{
				(*m).x = (*m).x - (TILE_SIZE / 2);				
				(*m).y = (*m).y - (TILE_SIZE / 2) * (-tan(rad));	
				if (rest((*m).y, TILE_SIZE) < TILE_SIZE - get_diff_ms(t1, (*game).t_door) * TILE_SIZE/1000)
				{
					if (get_diff_ms(t1, (*game).t_door) < 1000)
					 	(*game).lag.y = TILE_SIZE - get_diff_ms(t1, (*game).t_door) * TILE_SIZE/1000;
					else 
						(*game).lag.y = 0;
					return (r - (TILE_SIZE / 2) / cos(rad));
				}				
				else //ca passe
				{					
					(*m).x = (*m).x + (TILE_SIZE / 2);
					(*m).y = (*m).y + (TILE_SIZE / 2) * (-tan(rad));
				}
			}
			else if (get_door_status(*game, (int)((*m).y / TILE_SIZE), (int)(*m).x / TILE_SIZE) == 3)
			{
				(*m).x = (*m).x - (TILE_SIZE / 2);				
				(*m).y = (*m).y - (TILE_SIZE / 2) * (-tan(rad));	
				if (rest((*m).y, TILE_SIZE) < get_diff_ms(t1, (*game).t_door) * TILE_SIZE/1000) // arret				
				{
					if (get_diff_ms(t1, (*game).t_door) < 1000)
						(*game).lag.y = get_diff_ms(t1, (*game).t_door) * TILE_SIZE/1000;								
					else 
						(*game).lag.y = 0;
					return (r - (TILE_SIZE / 2) / cos(rad));
				}				
				else // 
				{			
					(*m).x = (*m).x + (TILE_SIZE / 2);
					(*m).y = (*m).y + (TILE_SIZE / 2) * (-tan(rad));		
				}
			}			
		}
		else	
			(*game).side = 'D';	
		}
		
	}
}
//printf("inter m.y %f, inter m.x %f\n", (*m).y, (*m).x);

// -PI/2 < rad < PI/2, cos(rad) > 0
// p.x = i * TILE_SIZE + dx
// p.y = j * TILE_SIZE + dy
double	ray_inter_v2(t_game *game, t_point p, double rad, t_point *m)
{
	double	d;
	int		dx;
	double	r;
	int		count;
	t_nsec t1;

	// t_point	m;
	if (cos(rad) <= 0)
		return (WIN_W * WIN_W);
	*m = p;
	d = 0;
	r = 0;
	count = 1;
	while (1)
	{
		// (*game).lag = 0;
		dx = (int)(*m).x % TILE_SIZE;
		if (dx == 0) // on est sur une h
			r = r + TILE_SIZE / cos(rad);
		else // depart si pas sur une h
			r = (TILE_SIZE - dx) / cos(rad);
		d = r * sin(rad);
		(*m).y = p.y - d;
		(*m).x = ((int)p.x - (int)p.x % TILE_SIZE) + count * TILE_SIZE;
		count++;
		if (is_outside_map((*game).map, *m) == 1)
			return (r);		
		// hit wall?
		if ((*game).map.tab[(int)((*m).y / TILE_SIZE)][(int)(*m).x / TILE_SIZE] == '1')			
			return (r);
		if ((*game).map.tab[(int)((*m).y / TILE_SIZE)][(int)(*m).x / TILE_SIZE] == 'D')				
		{
		if (is_side_door_v2(rad, (*m).y) == 0)
		{
			if (tan(rad) == 0 )
				printf("zero v2\n");
			clock_gettime(CLOCK_MONOTONIC, &t1);			
			if (get_door_status(*game, (int)((*m).y / TILE_SIZE), (int)(*m).x / TILE_SIZE) == 0) // closed
			{
				(*m).x = (*m).x + (TILE_SIZE / 2);
				// if (tan(rad) != 0 )
					(*m).y = (*m).y - (TILE_SIZE / 2) * tan(rad);
				return (r + (TILE_SIZE / 2) / cos(rad));
			}			
			else if (get_door_status(*game, (int)((*m).y / TILE_SIZE), (int)(*m).x / TILE_SIZE) == 1)
			{
				(*m).x = (*m).x + (TILE_SIZE / 2);
				// if (tan(rad) != 0 )
					(*m).y = (*m).y - (TILE_SIZE / 2) * tan(rad);
				if (rest((*m).y, TILE_SIZE) < TILE_SIZE - get_diff_ms(t1, (*game).t_door) * TILE_SIZE/1000)
				{
					if (get_diff_ms(t1, (*game).t_door) < 1000)
						(*game).lag.y = TILE_SIZE - get_diff_ms(t1, (*game).t_door) * TILE_SIZE/1000;
					else
						(*game).lag.y = 0;	
					return (r + (TILE_SIZE / 2) / cos(rad));
				}				
				else //ca passe
				{					
					(*m).x = (*m).x - (TILE_SIZE / 2);
					// if (tan(rad) != 0 )
						(*m).y = (*m).y + (TILE_SIZE / 2) * tan(rad);
				}
			}
			else if (get_door_status(*game, (int)((*m).y / TILE_SIZE), (int)(*m).x / TILE_SIZE) == 3)
			{
				(*m).x = (*m).x + (TILE_SIZE / 2);
				// if (tan(rad) != 0 )
					(*m).y = (*m).y - (TILE_SIZE / 2) * tan(rad);
				if (rest((*m).y, TILE_SIZE) < get_diff_ms(t1, (*game).t_door) * TILE_SIZE/1000) // arret
				
				{
					if (get_diff_ms(t1, (*game).t_door) < 1000)
						(*game).lag.y = get_diff_ms(t1, (*game).t_door) * TILE_SIZE/1000;		
					else 
						(*game).lag.y = 0;
					return (r + (TILE_SIZE / 2) / cos(rad));
				}				
				else // 
				{						
					(*m).x = (*m).x - (TILE_SIZE / 2);					
					(*m).y = (*m).y + (TILE_SIZE / 2) * tan(rad);
				}
			}
		}
		else	
			(*game).side = 'D';		
		}
	}
}

int	is_outside_map(t_map map, t_point m)
{
	// if (m.y < 0 || m.x < 0 || m.y > TILE_SIZE * map.rows
	// 		||	m.x > TILE_SIZE * map.cols)
	if (m.y < 0 || (size_t)m.y / TILE_SIZE > map.rows - 1 || m.x < 0
		|| (size_t)(m.x / TILE_SIZE) > map.cols - 1)
		return (1);
	return (0);
}

// printf("mx = %f\n", m.x);
// printf("my = %f\n", m.y);
// printf("j = %ld\n", (size_t)m.y / TILE_SIZE);
// printf("i = %ld\n", (size_t)(m.x / TILE_SIZE));
// printf("rows = %ld\n", map.rows);
// printf("cols = %ld\n", map.cols);

// printf("j = %d\n", (int)(m.y / TILE_SIZE));
// printf("i = %d\n", (int)m.x / TILE_SIZE);
// printf("my = %f\n", m.y);
// printf("mx = %f\n", m.x);
// printf("rows = %ld\n", map.rows);
// printf("cols = %ld\n", map.cols);
// printf("ici 2\n");

// printf("count = %d\n", count);
// printf("my = %f\n", m.y);
// printf("dy = %d\n", dy);
// printf("r = %f\n", r);
// printf("d = %f\n", d);
// printf("my = %f\n", m.y);
// printf("j = %d\n", (int)m.y / TILE_SIZE);
// printf("mx = %f\n", m.x);
// printf("mx / T = %f\n", m.x / TILE_SIZE);
// printf("i = %d\n", (int)(m.x / TILE_SIZE));
// (sin(rad) / fabs(sin(rad)))

// printf("j = %d\n", (int)(m.y / TILE_SIZE));
// printf("i = %d\n", (int)m.x / TILE_SIZE);
// printf("my = %f\n", m.y);
// printf("mx = %f\n", m.x);

/****** draft */

// For testing draw_line :
// t_point a, b;
// a.x = 30;
// a.y = 28;
// b.x = 150;
// b.y = 50;
// draw_line(&img, a, b);
// printf("ax %d ay %d\n", (int)a.x, (int)a.y);
// printf("bx %d by %d\n", (int)b.x, (int)b.y);

// double	test(double r)
// {
// 	r = r + 3;
// 	if (r > 12)
// 		return (r);
// 	else
// 		return (test(r));
// }

//** ray inter en recursif (pas la derniere version -> a corriger) */
// double	ray_inter_h(t_map map, t_point p, double rad, double r, int count)
// {
// 	double	d;
// 	t_point	m;
// 	int		dy;

// 	dy = p.y % TILE_SIZE;
// 	if (dy == 0) // on est sur une h
// 	{
// 		r = r + TILE_SIZE / sin(rad);
// 		// d = TILE_SIZE / tan(rad);
// 	}
// 	else
// 	{
// 		r = r + dy / sin(rad);
// 		// d = dy / tan(rad);
// 	}
// 	printf("r = %f\n", r);
// 	d = r * cos(rad);
// 	printf("d = %f\n", d);
// 	m.x = p.x + d;
// 	m.y = (p.y - dy) - count * TILE_SIZE;
// 	count++;
// 	printf("count = %d\n", count);
// 	//
// 	printf("j = %d\n", (p.y - dy) / TILE_SIZE);
// 	printf("i = %d\n", (int)((p.x + d) / TILE_SIZE));
// 	// hit wall?
// 	if (map.tab[m.y / TILE_SIZE][(int)(m.x / TILE_SIZE)] == '1')
// 		return (r);
// 	else
// 		return (printf("ici\n"), ray_inter_h(map, m, rad, r, count));
// }

// if ((int)m.y / TILE_SIZE < 0 || (int)(m.x / TILE_SIZE) < 0)
// {
// 	printf("break %f\n", r);
// 	return (0);
// 	//break ;
// }
// if ((int)m.y / TILE_SIZE > (int)map.rows - 1 || (int)(m.x
// 		/ TILE_SIZE) > (int)map.cols - 1)
// {
// 	printf("break 2 %f\n", r);
// 	return (0);
// 	//break ;
// }

// // p.x = i * TILE_SIZE + dx
// // p.y = j * TILE_SIZE + dy = 0
// double	ray_inter_test(t_map map, t_point p, double rad)
// {
// 	double	d;
// 	t_point	m;
// 	double	r;
// 	int		count;

// 	// int		dy;
// 	if (sin(rad) == 0)
// 		return (MAP_W * MAP_W);
// 	m = p;
// 	d = 0;
// 	r = 0;
// 	count = 1;
// 	while (1)
// 	{
// 		// on est sur h, dy = 0
// 		if (map.tab[((int)p.y - TILE_SIZE) / TILE_SIZE][(int)(p.x
// 				/ TILE_SIZE)] == '1')
// 			return (r);
// 		r = r + TILE_SIZE / sin(rad); // printf("r %f\n", r);
// 		d = r * cos(rad);             // printf("d %f\n", d);
// 		m.x = p.x + d;
// 		printf("m.x %f\n", m.x);
// 		m.y = ((int)p.y - (int)p.y % TILE_SIZE) - count * TILE_SIZE;
// 		printf("m.y %f\n", m.y);
// 		count++;
// 		printf("j = %d\n", (int)m.y / TILE_SIZE);
// 		printf("i = %d\n", (int)(m.x / TILE_SIZE));
// 		if (m.y < 0 || m.x < 0 || m.y > TILE_SIZE * map.rows || m.x > TILE_SIZE
// 			* map.cols)
// 			return (r); // printf("break %f\n", r),
// 						// hit wall?
// 						// if ((int)p.y % TILE_SIZE == 0)
// 						// {
// 						// 	if (map.tab[((int)m.y
// 									- TILE_SIZE)/ TILE_SIZE][(int)(m.x
// 						//			/ TILE_SIZE)] == '1')
// 						// 	return (r);
// 						// }
// 						// if (map.tab[(int)m.y / TILE_SIZE][(int)(m.x
// 								/ TILE_SIZE)] == '1')
// 						// 	return (r);
// 	}
// }

/******* */
