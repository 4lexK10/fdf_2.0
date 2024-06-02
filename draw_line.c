/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:43:04 by akloster          #+#    #+#             */
/*   Updated: 2024/06/02 17:00:58 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	swap_coordinates(t_2d_point *i, t_2d_point *f)
{
	int	temp;

	temp = i->x;
	i->x = i->y;
	i->y = temp;
	if (!f)
		return ;
	temp = f->x;
	f->x = f->y;
	f->y = temp;
}

static void	switch_values(t_2d_grid *head, int res)
{
	while (head != NULL)
	{
		if (res == 1 || res == 3)
			swap_coordinates(&(head->point), NULL);
		if (res == 2 || res == 3)
			head->point.y *= -1;
		head = head->next;
	}
}

static int	find_case(t_2d_point *i, t_2d_point *f)
{
	t_2d_point	temp;
	int			dx;
	int			dy;

	dx = f->x - i->x;
	dy = f->y - i->y;
	temp = *i;
	if (dx < 0)
	{
		*i = *f;
		*f = temp;
		return (find_case(i, f));
	}
	else if (dx * dy < 0)
	{
		i->y = -i->y;
		f->y = -f->y;
		return (find_case(i, f) + 2);
	}
	else if (dy > dx)
	{
		swap_coordinates(i, f);
		return (1);
	}
	return (0);
}

int	draw_line(t_2d_point i, t_2d_point f, t_data *img)
{
	t_2d_grid	*head;
	t_2d_grid	*temp;
	int			res;

	head = NULL;
	res = find_case(&i, &f);
	if (create_line(i, f, &head))
		return (1);
	switch_values(head, res);
	temp = head;
	while (temp != NULL)
	{
		my_mlx_pixel_put(img, temp->point.x, temp->point.y, 0xffffff);
		temp = temp->next;
	}
	grid_2d_lstclear(&head);
	return (0);
}
