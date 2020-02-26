# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/18 17:54:38 by edal--ce          #+#    #+#              #
#    Updated: 2020/02/26 05:37:53 by edal--ce         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out

SRCS = 	src/fonctions.c \
		src/keys.c 		\
		src/wall_cast.c	\
		src/wc_utils.c \
		src/screenshot.c \
		src/cub_loader.c \
		src/spritecast.c \
		src/movement.c 	\
		src/texture_loaders.c \
		src/floor_cast.c \
		src/more_functions.c \
		src/start_pos.c \
		src/load_utils.c \
		src/minmap.c 	\
		src/mouse.c 	\
		src/init.c 	\
		src/nice.c 	\
		src/other_functions.c \
		main.c
		

INCL = header/

HEADER = $(INCL)header.h

CC = gcc

LIBFT = libft/libft.a

CFLAGS = -O3 -Wall -Wextra -g3 -flto -march=native -D BONUS #-Wpadded #-fsanitize=address#-Wpadded

FRMWORKS = -framework AppKit -framework OpenGL

LIBLINK = -L ./minilibx_opengl_20191021/ -lmlx $(FRMWORKS)

LIB = libft/

OBJS = ${SRCS:.c=.o}

all : $(NAME)

.c.o:
	${CC} ${CFLAGS} -I $(HEADER) -c $< -o ${<:.c=.o}

libft :
	@$(MAKE) -C libft

$(NAME): libft $(OBJS) $(HEADER)
	gcc -I $(HEADER) -I ./minilibx_opengl_20191021/ $(LIBFT) $(OBJS) $(LIBLINK)

cleanlibft :
	$(MAKE) -C libft clean

fcleanlibft :
	$(MAKE) -C libft fclean

clean : cleanlibft
	$(RM) $(OBJS)

fclean : clean fcleanlibft
	$(RM) $(NAME)
	rm -rf a.out a.out.dSYM

re : fclean all

.PHONY : all clean fclean re libft cleanlibft fcleanlibft
