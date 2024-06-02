/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:28:52 by akloster          #+#    #+#             */
/*   Updated: 2024/06/03 00:24:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fill_line(int *line, int y, int max_x, int **map)
{
	int	i;
	int	x;

	i = -1;
	x = 0;
	while (x < max_x)
	{
		line[++i] = iso_proj(&map[y][x], 0, 1);
		line[++i] = iso_proj(&map[y][x], 1, 1);
		x += 2;
	}
}

int	**create_2d(int **map_3d, t_2d_point dimensions)
{
	int	i;
	int	y;
	int	**map;

	i = -1;
	y = -1;
	map = (int **)malloc(sizeof(int *) * dimensions.y);
	if (!map)
	{
		free_map(&map_3d, dimensions);
		return (NULL);
	}
	while (++i < dimensions.y)
	{
		map[i] = (int *)malloc(sizeof(int) * (dimensions.x * 2));
		if (!map[i])
		{
			free_map(&map, dimensions);
			free_map(&map_3d, dimensions);
			return (NULL);
		}
	}
	while (++y < dimensions.y)
		fill_line(map[y], y, dimensions.x * 2, map_3d);
	return (map);
}
