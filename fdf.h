/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 10:23:09 by akloster          #+#    #+#             */
/*   Updated: 2024/03/23 10:23:09 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "/usr/local/include/mlx.h"
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# define HEIGHT 1300
# define WIDTH	2000

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	img;
}			t_vars;

typedef struct s_2d_point
{
	int	x;
	int	y;
}		t_2d_point;

typedef struct s_2d_grid
{
	t_2d_point			point;
	struct s_2d_grid	*next;
}						t_2d_grid;

typedef struct s_3d_grid
{
	int					x;
	int					y;
	int					z;
	int					color;
	struct s_3d_grid	*next;
}						t_3d_grid;

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		grid_2d_lstclear(t_2d_grid **lst);
void		free_ptr_array(char ***s);
int			draw_line(t_2d_point i, t_2d_point f, t_data *img);
void		calibrate(int **map, int **map_3d, t_2d_point dimensions);
int			iso_proj(int *point, int want_y, int scale);
void		my_free(char **str);
void		free_map(int ***map, t_2d_point dimensions);
t_2d_point	get_array_dimensions(char *path);
int			**create_3d(int fd, t_2d_point dimensions);
int			**create_2d(int **map_3d, t_2d_point dimensions);
void		min_point(int **map, t_2d_point *min_x,
				t_2d_point *min_y, t_2d_point dimensions);
t_2d_point	bresenham(t_2d_point i, t_2d_point f,
				int *param, t_2d_grid *head);
void		clean_line(char **str);
float		iso_prof(int *point, int want_y);
int			put_longitude(int **map, t_data *img, t_2d_point dimensions);
void		max_p(int **map, t_2d_point *max_x,
				t_2d_point *max_y, t_2d_point d);
int			create_line(t_2d_point i, t_2d_point f, t_2d_grid **head);

#endif
