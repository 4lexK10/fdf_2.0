
#include "fdf.h"

int check_map(int **map)
{
    /*
    
    1. too small (< 1 point)
    2. check if too big
    
    */
    ;
}

/* Types of errors

    -open/close failure (has errno)
    -malloc error       (has errno) dont forget: ft_strtrim, ft_split, get_next_line
    -map                (has NOT errno)
    -arg nbr            (has NOT errno)

*/

int ft_error(char *error_msg, int error_nbr)
{
    if (!error_nbr)
        ft_putendl_fd(error_msg, 2);
    else
        perror(error_msg);
    exit(EXIT_FAILURE);
}
