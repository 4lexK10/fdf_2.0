/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:03:22 by akloster          #+#    #+#             */
/*   Updated: 2024/05/28 14:43:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clean_line(char **str)
{
	char *line;

	if (!(*str))
		return ;
	line = ft_strtrim(*str, "\n");
	my_free(str);
	if (!line)
		return ;
	*str = line;
}


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
	raw_z = ft_split(raw_line, ' ');  // check if split is protected if NULL is passed
	if (!raw_z)
		return (my_free(&raw_line), FAIL);
	while (x < max_x)
	{
		line[++i] = x;
		line[++i] = y;
		line[++i] = ft_atoi(raw_z[x++]);
	}
	return (SUCCESS);
}

int	**create_3d(int fd, t_2d_point dimensions)
{
	int		i;
	int		**map;

	i = -1;
	map = (int **)malloc(sizeof(int *) * dimensions.y);
	if (!map)
		return (NULL);
	while (++i < dimensions.y)
	{
		map[i] = (int *)malloc(sizeof(int) * (dimensions.x * 3));
		if (!map[i] || fill_line(map[i], i, dimensions.x, fd) == FAIL)
			return (free_map(&map, dimensions), NULL);
	}
	if ()
	return (map);
}
