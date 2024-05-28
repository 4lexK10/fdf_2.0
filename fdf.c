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
	if (dimensions.x == 0 || (dimensions.x == 1 && dimensions.y == 1))
		return (1);
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

static int	mlx_close(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int main(int ac, char **av)
{
	t_vars	vars;

	if (ac != 2)
		return (0);
	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (0);
	vars.win = mlx_new_window (vars.mlx , WIDTH, HEIGHT, "fdf");
	vars.img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bpp, &vars.img.line_length, &vars.img.endian);
	if (create_load_map(&vars.img, av[1]))
		return (0);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_hook(vars.win, 2, 1L<<0, mlx_close, &vars);
	mlx_hook(vars.win, 4, 1L<<2, mlx_close, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
