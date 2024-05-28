# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akloster <akloster@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/23 10:23:17 by akloster          #+#    #+#              #
#    Updated: 2024/03/23 10:23:17 by akloster         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	cc

NAME			=	fdf

CFLAGS			=	-Wall -Wextra -Werror 

INCLUDES		=	-I /usr/local/include

SRC				=	fdf.c free_functions.c create_3d.c img_build.c \
					create_2d.c draw_line.c calibrate.c testing.c

LIB				=	-L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

SRC_GNL			= 	gnl/get_next_line.c gnl/get_next_line_utils.c

LIBFT			=	libft/libft.a

OBJ_DIR			=	objs/

OBJ				=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

RM				=	rm -rf

$(NAME):		$(OBJ_DIR) $(OBJ)
				make -C./libft
				$(CC) $(CFLAGS) $(INCLUDES) $(SRC_GNL) $(OBJ) $(LIB) $(LIBFT) -o $@

all:			$(NAME)

$(OBJ_DIR)%.o:	%.c
				$(CC) $(CFLAGS) -c $< -o $@

%.o: 			%.c
				$(CC) $(CFLAGS) $< -o $@


$(OBJ_DIR):	
				@mkdir -p $(OBJ_DIR)

clean:
				make clean -C./libft
				$(RM) $(OBJ)

fclean:			clean
				make fclean -C./libft
				$(RM) $(OBJ) $(NAME) $(OBJ_DIR)

re:				fclean $(NAME)


.PHONY:			all clean fclean re
