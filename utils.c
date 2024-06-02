/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:09:42 by akloster          #+#    #+#             */
/*   Updated: 2024/06/02 16:57:22 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

float	iso_prof(int *point, int want_y)
{
	if (want_y)
		return (sqrt(6) / 6 * ((point[0]) + (point[1]))
			- sqrt(4) / 3 * (point[2]));
	return (sqrt(2) / 2 * ((point[0]) - (point[1])));
}

void	min_point(int **map, t_2d_point *min_x, t_2d_point *min_y, t_2d_point d)
{
	int	i;
	int	j;

	i = -1;
	while (++i < d.y)
	{
		j = 0;
		while (j / 3 < d.x)
		{
			if (iso_prof(&map[i][j], 0) < iso_prof(&map[min_x->y][min_x->x], 0))
			{
				min_x->x = j;
				min_x->y = i;
			}
			if (iso_prof(&map[i][j], 1) < iso_prof(&map[min_y->y][min_y->x], 1))
			{
				min_y->x = j;
				min_y->y = i;
			}
			j += 3;
		}
	}
}

t_2d_point	bresenham(t_2d_point i, t_2d_point f, int *param, t_2d_grid *head)
{
	t_2d_point	pixel;

	pixel = i;
	if (!head)
		return (pixel);
	else
	{
		while (head->next != NULL)
			head = head->next;
		pixel = head->point;
	}
	if (*param < 0)
		*param += 2 * (f.y - i.y);
	else
	{
		*param += 2 * (f.y - i.y) - 2 * (f.x - i.x);
		++pixel.y;
	}
	++pixel.x;
	return (pixel);
}

t_2d_point	get_array_dimensions(char *path)
{
	t_2d_point	dimensions;
	char		**line;
	char		*output;
	int			fd;

	dimensions.x = 0;
	dimensions.y = 1;
	fd = open(path, O_RDONLY);
	output = get_next_line(fd);
	clean_line(&output);
	line = ft_split(output, ' ');
	my_free(&output);
	if (!line)
		return (dimensions);
	while (line[++dimensions.x] != NULL)
		;
	free_ptr_array(&line);
	output = get_next_line(fd);
	while (output != NULL)
	{
		++dimensions.y;
		my_free(&output);
		output = get_next_line(fd);
	}
	return (my_free(&output), close(fd), dimensions);
}
