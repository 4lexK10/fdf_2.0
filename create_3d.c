/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:03:22 by akloster          #+#    #+#             */
/*   Updated: 2024/06/03 01:36:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fill_line(int *line, int y, int max_x,	int fd)
{
	char	**raw_z;
	char	*raw_line;
	int		x;
	int		i;

	x = 0;
	i = -1;
	raw_line = get_next_line(fd);
	clean_line(&raw_line);
	raw_z = ft_split(raw_line, ' ');
	if (!raw_z)
	{
		my_free(&raw_line);
		return (1); //what hapens if raw_line = NULL (&NULL?)
	}
	while (x < max_x)
	{
		line[++i] = x;
		line[++i] = y;
		line[++i] = ft_atoi(raw_z[x++]);
	}
	my_free(&raw_line);
	free_ptr_array(&raw_z);
	return (0);
}

static int	check_map(int **map, t_2d_point dimensions)
{
	t_2d_point	min_x;
	t_2d_point	min_y;
	t_2d_point	max_x;
	t_2d_point	max_y;

	max_x.x = 0;
	max_x.y = 0;
	max_y.x = 0;
	max_y.y = 0;
	min_x.x = 0;
	min_x.y = 0;
	min_y.x = 0;
	min_y.y = 0;
	max_p(map, &max_x, &max_y, dimensions);
	min_point(map, &min_x, &min_y, dimensions);
	if ((iso_proj(&map[max_x.y][max_x.x], 0, 1)
		- iso_proj(&map[min_x.y][min_x.x], 0, 1)) > WIDTH)
		return (1);
	if (iso_proj(&map[max_y.y][max_y.x], 1, 1)
		- iso_proj(&map[min_y.y][min_y.x], 1, 1) > HEIGHT)
		return (1);
	return (0);
}

int	**create_3d(int fd, t_2d_point dimensions)
{
	int		i;
	int		**map;

	if (fd == -1)
		return (NULL);
	i = -1;
	map = (int **)malloc(sizeof(int *) * dimensions.y);
	if (!map)
		return (NULL);
	while (++i < dimensions.y)
	{
		map[i] = (int *)malloc(sizeof(int) * (dimensions.x * 3));
		if (!map[i] || fill_line(map[i], i, dimensions.x, fd) == 1)
		{
			free_map(&map, dimensions);
			return (NULL);
		}
	}
	if (check_map(map, dimensions))
	{
		free_map(&map, dimensions);
		return (NULL);
	}
	return (map);
}
