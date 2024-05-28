/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:07:44 by akloster          #+#    #+#             */
/*   Updated: 2024/05/19 17:54:14 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	grid_2d_lstclear(t_2d_grid **lst)
{
	t_2d_grid	*temp;
	t_2d_grid	*prev;

	if (!lst || !(*lst))
		return ;
	temp = *lst;
	*lst = NULL;
	while (temp != NULL)
	{
		prev = temp;
		temp = temp->next;
		free(prev);
	}
}

void	free_map(int ***map, t_2d_point dimensions)
{
	int	i;

	i = -1;
	if (*map && **map)
	{
		while ((*map)[++i] && i < dimensions.y)
		{
			free((*map)[i]);
			(*map)[i] = NULL;
		}
	}
	if (*map)
	{
		free(*map);
		*map = NULL;
	}
}

void	free_ptr_array(char ***s)
{
	int	i;

	if (!**s || !*s)
		return ;
	i = 0;
	if (*s != NULL)
	{
		while ((*s)[i] != NULL)
		{
			free((*s)[i]);
			(*s)[i] = NULL;
			++i;
		}
		free(*s);
		*s = NULL;
	}
}

void	my_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

