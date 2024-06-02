/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:09:19 by akloster          #+#    #+#             */
/*   Updated: 2024/06/02 16:57:40 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	put_longitude(int **map, t_data *img, t_2d_point dimensions)
{
	int			x;
	int			y;
	t_2d_point	i;
	t_2d_point	f;

	x = 0;
	while (x / 2 < dimensions.x)
	{
		y = -1;
		while (++y < dimensions.y - 1)
		{
			i.x = map[y][x];
			i.y = map[y][x + 1];
			f.x = map[y + 1][x];
			f.y = map[y + 1][x + 1];
			if (draw_line(i, f, img))
				return (1);
		}
		x += 2;
	}
	return (0);
}

int	iso_proj(int *point, int want_y, int scale)
{
	if (want_y)
		return ((int)(sqrt(6) / 6 * ((scale * point[0]) + (scale * point[1]))
			- sqrt(4) / 3 * (scale * point[2])));
	return ((int)(sqrt(2) / 2 * ((scale * point[0]) - (scale * point[1]))));
}

void	max_p(int **map, t_2d_point *max_x, t_2d_point *max_y, t_2d_point d)
{
	int			i;
	int			j;

	i = -1;
	while (++i < d.y)
	{
		j = 0;
		while (j / 3 < d.x)
		{
			if (iso_prof(&map[i][j], 0) > iso_prof(&map[max_x->y][max_x->x], 0))
			{
				max_x->x = j;
				max_x->y = i;
			}
			if (iso_prof(&map[i][j], 1) > iso_prof(&map[max_y->y][max_y->x], 1))
			{
				max_y->x = j;
				max_y->y = i;
			}
			j += 3;
		}
	}
}

static	t_2d_grid	*create_2d_point(t_2d_grid **head, t_2d_point pixel)
{
	t_2d_grid	*new_pixel;
	t_2d_grid	*temp;

	new_pixel = (t_2d_grid *)malloc(sizeof(t_2d_grid));
	if (!new_pixel)
		return (NULL);
	new_pixel->point = pixel;
	new_pixel->next = NULL;
	if (!(*head))
		*head = new_pixel;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_pixel;
	}
	return (*head);
}

int	create_line(t_2d_point i, t_2d_point f, t_2d_grid **head)
{
	int			incr;
	int			decision_param;
	t_2d_point	pixel;

	incr = i.x;
	decision_param = 2 * (f.y - i.y) - (f.x - i.x);
	while (incr <= f.x)
	{
		pixel = bresenham(i, f, &decision_param, *head);
		*head = create_2d_point(head, pixel);
		++incr;
		if (!(*head))
		{
			grid_2d_lstclear(head);
			return (1);
		}
	}
	return (0);
}

void	clean_line(char **str)
{
	char	*line;

	if (!(*str))
		return ;
	line = ft_strtrim(*str, "\n");
	my_free(str);
	if (!line)
	{
		*str = NULL;
		return ;
	}
	*str = line;
}
