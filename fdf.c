/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 10:23:00 by akloster          #+#    #+#             */
/*   Updated: 2024/03/23 10:23:00 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	put_grid(int **map, t_data *img, t_2d_point dimensions)
{
	int			**temp;
	int			x;
	int			y;
	t_2d_point	i;
	t_2d_point	f;

	y = -1;
	temp = map;
	while (++y < dimensions.y)
	{
		x = 0;
		while (x / 2 < dimensions.x - 1)
		{
			i.x = map[y][x];
			i.y = map[y][x + 1];
			f.x = map[y][x + 2];
			f.y = map[y][x + 3];
			/* printf("i(%d, %d), f(%d, %d)\n", i.x, i.y, f.x, f.y); */
			draw_line(i, f, img);
			x += 2;
		}
	}
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
			draw_line(i, f, img);
		}
		x += 2;
	}
}

static	int	create_load_map(t_data *img, char *path)
{
	int			fd;
	t_2d_point	dimensions;
	int			**map_3d;
	int			**map;

	dimensions = get_array_dimensions(path);
	if (dimensions.x == 0)
		return (/* error(),  */0);  //need error function
	fd = open(path, O_RDONLY);
	map_3d = create_3d(fd, dimensions);
	close(fd);
	if (!map_3d)
		return (1);
	map = create_2d(map_3d, dimensions);
	if (!map)
		return (1);
	calibrate(map, map_3d, dimensions);
	put_grid(map, img, dimensions);
	return (free_map(&map, dimensions), free_map(&map_3d, dimensions), 0);
}

static int	mlx_close(int keycode, t_vars *vars, t_data *img)
{
	if (keycode == 53)
	{
		mlx_destroy_image(vars->mlx, img);
		mlx_destroy_window(vars->mlx, vars->win); // destroy img
	}
	return (0);
}

int main(int ac, char **av)
{
	t_vars	vars;
	t_data	img;

	if (ac != 2)
		return (0);
	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (0);
	vars.win = mlx_new_window (vars.mlx , WIDTH, HEIGHT, "fdf");
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	mlx_hook(vars.win, 2, 1L<<0, mlx_close, &vars);
	if (create_load_map(&img, av[1]))
		return (0);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}

/* 	for (t_2d_grid *tempi = head_2d; tempi->next->x > tempi->x; tempi = tempi->next)
	{
		for (t_2d_grid *temp = tempi; temp != NULL; temp = temp->under)
			my_mlx_pixel_put(&img, temp->x, temp->y, 0xffffff);
	} */
/* 	for (t_2d_grid *temp = head_2d->next->next; temp != NULL; temp = temp->under)
		my_mlx_pixel_put(&img, temp->x, temp->y, 0xffffff); */
/* 	for (t_2d_grid *temp = head_2d; temp != NULL; temp = temp->next)
	{	
		printf("(%d, %d) ", temp->point->x, temp->point->y);
		if (temp->next != NULL && temp->next->point->x < temp->point->x)
			printf("\n");
	} */
/* 	for (t_2d_grid *tempi = head_2d; tempi->next->point.x > tempi->point.x; tempi = tempi->next)
	{
		for (t_2d_grid *temp = tempi; temp != NULL; temp = temp->under)
			my_mlx_pixel_put(&img, temp->point.x, temp->point.y, 0xffffff);
	} */
/* 	for (t_2d_grid *temp = head_2d; temp != NULL; temp = temp->next)
	{	
		printf("(%d, %d) ", temp->point.x, temp->point.y);
		if (temp->next != NULL && temp->next->point.x < temp->point.x)
			printf("\n");
	} */
/* 	for (t_2d_grid *tempi = head_2d; (nbr--) >= 0; tempi = tempi->next)
	{
		for (t_2d_grid *temp = tempi; temp != NULL; temp = temp->under)
			my_mlx_pixel_put(&img, temp->point.x, temp->point.y, 0xffffff);
	} */
