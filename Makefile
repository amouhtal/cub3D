# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/19 13:51:36 by amouhtal          #+#    #+#              #
#    Updated: 2020/12/08 13:50:34 by amouhtal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

NAMA = cub.a

SRC = 	./utils/utils.c ./sprite/sprit.c ./sprite/sprite_util.c ./utils/intialise.c \
		./pars/ft_atoi.c ./pars/get_next_line.c \
		./pars/get_next_line_utils.c ./pars/pars.c \
		./pars/manage_table.c cub.c keypress.c ./pars/pars_utils.c \
		raycast.c ./savebmp/bmp.c ./pars/initialiseparse.c \
		./pars/floor_ceil.c draw_screen.c ./savebmp/bmp_utils.c \
		./pars/pars_utils2.c ./pars/pars_utils3.c raycast_utlis.c \
		

OBJ=$(SRC:.c=.o)

CFLAGS = 

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAMA) $(OBJ)
	gcc $(CFLAGS) $(NAMA) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo 'SUCCESS!'

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAMA)

re: fclean all

