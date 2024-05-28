#include "fdf.h"

void	print_map(int **map, t_2d_point dimensions, int want_3d)
{
	int i;
	int	j;

	i = -1;
	if (want_3d)
	{
		while (++i < dimensions.y)
		{
			j = 0;
			while (j / 3 < dimensions.x)
			{
				printf("(%d, %d, %d) ", map[i][j], map[i][j + 1], map[i][j + 2]);
				j += 3;
			}
			printf("\n");
		}
		return ;
	}
	while (++i < dimensions.y)
	{
		j = 0;
		while (j / 2 < dimensions.x)
		{
			printf("(%d, %d) ", map[i][j], map[i][j + 1]);
			j += 2;
		}
		printf("\n");
	}
}
