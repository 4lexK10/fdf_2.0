/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calibrate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:22:31 by akloster          #+#    #+#             */
/*   Updated: 2024/05/28 20:51:07 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_min(int **map, t_2d_point dimensions, int want_y)
{
	int	min_x;
	int	min_y;
	int	i;
	int	j;

	min_x = 0;
	min_y = 0;
	i = -1;
	while (++i < dimensions.y)
	{
		j = 0;
		while (j / 2 < dimensions.x)
		{
			if (map[i][j] < min_x)
				min_x = map[i][j];
			if (map[i][j + 1] < min_y)
				min_y = map[i][j + 1];
			j += 2;
		}
	}
	if (want_y)
		return (min_y);
	return (min_x); 
}

static void	max_point(int **map, t_2d_point *max_x, t_2d_point *max_y, t_2d_point dimensions)
{
	int			i;
	int			j;

	i = -1;
	while (++i < dimensions.y)
	{
		j = 0;
		while (j / 3 < dimensions.x)
		{
			if (iso_projf(&map[i][j], 0) > iso_projf(&map[max_x->y][max_x->x], 0))
			{	
				max_x->x = j;
				max_x->y = i;
			}
			if (iso_projf(&map[i][j], 1) > iso_projf(&map[max_y->y][max_y->x], 1))
			{	
				max_y->x = j;
				max_y->y = i;
			}
			j += 3;
		}
	}
}

static void	set_1st_quad(int **map, t_2d_point dimensions)
{
	int	min_x;
	int	min_y;
	int	i;
	int	j;

	min_x = get_min(map, dimensions, 0);
	min_y = get_min(map, dimensions, 1);
	printf("minx %d miny %d\n", min_x, min_y);
	i = -1;
	while (++i < dimensions.y)
	{
		j = 0;
		while (j / 2 < dimensions.x)
		{
			if (min_x < 0)
				map[i][j] += -min_x;
			if (min_y < 0)
				map[i][j + 1] += -min_y;
			j += 2;
		}
	}
}

static int	check_scale_up(int **map_3d, t_2d_point dimensions)
{
	t_2d_point	min_x;
	t_2d_point	min_y;
	t_2d_point	max_x;
	t_2d_point	max_y;
	int			scale;

	max_x.x = 0;
	max_x.y = 0;
	max_y.x = 0;
	max_y.y = 0;
	min_x.x = 0;
	min_x.y = 0;
	min_y.x = 0;
	min_y.y = 0;
	scale = 2;
	max_point(map_3d, &max_x, &max_y, dimensions);
	min_point(map_3d, &min_x, &min_y, dimensions);
	while ((iso_proj(&map_3d[max_x.y][max_x.x], 0, scale) - iso_proj(&map_3d[min_x.y][min_x.x], 0, scale)) < WIDTH &&
	(iso_proj(&map_3d[max_y.y][max_y.x], 1, scale) - iso_proj(&map_3d[min_y.y][min_y.x], 1, scale)) < HEIGHT)
		++scale;
	return (scale - 1);
}

void	calibrate(int **map, int **map_3d, t_2d_point dimensions)
{
	int scale_up;
	int i;
	int j;
	int	*point_3d;

	i = -1;
/* 	print_map(map, dimensions, 0); */
	/* set_1st_quad(map, dimensions); */
	scale_up = check_scale_up(map_3d, dimensions);
	if (scale_up == -1)
		printf("okkkkk\n");
	while (++i < dimensions.y)
	{
		j = 0;
		while (j / 2 < dimensions.x)
		{
			point_3d = &map_3d[i][(j / 2) * 3];
			map[i][j] = iso_proj(point_3d, 0, scale_up);
			map[i][j + 1] = iso_proj(point_3d, 1, scale_up);
			j += 2;
		}
	}
	set_1st_quad(map, dimensions);
}
