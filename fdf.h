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

#ifndef	FDF_H
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
# define SUCCESS 1
# define FAIL    0

# include <stdio.h>//<<------ DELETE!!

typedef struct  s_data
{
	void        *img;
	char    	*addr;
	int	    	bpp;
	int		    line_length;
	int		    endian;
}               t_data;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct			s_2d_point
{
	int	x;
	int	y;
}						t_2d_point;

typedef struct			s_2d_grid
{
	t_2d_point			point;
	int					color;
	struct	s_2d_grid	*next;
	struct	s_2d_grid	*under;
}						t_2d_grid;

typedef struct			s_3d_grid
{
	int					x;
	int					y;
	int					z;
	int					color;
	struct	s_3d_grid	*next;
}						t_3d_grid;

typedef struct	s_3x1
{
	float			x;
	float			y;
	float			z;
}				t_3x1;

typedef struct s_3x3
{
	float			x_x;
	float			x_y;
	float			x_z;
	float			y_x;
	float			y_y;
	float			y_z;
	float			z_x;
	float			z_y;
	float			z_z;
}				t_3x3;

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		grid_2d_lstclear(t_2d_grid **lst);
void		free_ptr_array(char ***s);
int			draw_line(t_2d_point i, t_2d_point f, t_data *img);
void    	put_circle(int r, int x, int y, t_data *img);  				// <---- TEST (delete!)
void		put_square(int a, int center_x, int center_y, t_data *img); // <---- TEST (delete!)
void		print_map(int **map, t_2d_point dimensions, int want_3d);      // <---- TEST (delete!)
void		calibrate(int **map, int **map_3d, t_2d_point dimensions);
int			iso_proj(int *point, int want_y, int scale);
void		my_free(char **str);
void		free_map(int ***map, t_2d_point dimensions);
t_2d_point	get_array_dimensions(char *path);
int			**create_3d(int fd, t_2d_point dimensions);
int			**create_2d(int **map_3d, t_2d_point dimensions);
void		min_point(int **map, t_2d_point *min_x, t_2d_point *min_y, t_2d_point dimensions);
t_2d_point	bresenham_algo(t_2d_point i, t_2d_point f, int *param, t_2d_grid *head);
void		clean_line(char **str);
float		iso_projf(int *point, int want_y);

#endif
