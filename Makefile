# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/18 17:54:38 by edal--ce          #+#    #+#              #
#    Updated: 2020/04/14 16:03:08 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out

SRCS = 	src/fonctions.c 		\
		src/keys.c 				\
		src/wall_cast.c			\
		src/wc_utils.c 			\
		src/screenshot.c 		\
		src/cub_loader.c 		\
		src/spritecast.c 		\
		src/movement.c 			\
		src/texture_loaders.c 	\
		src/floor_cast.c 		\
		src/more_functions.c 	\
		src/other_functions.c 	\
		src/start_pos.c 		\
		src/new_parse.c 		\
		src/load_utils.c 		\
		src/mouse.c 			\
		src/init.c 				\
		src/menu.c 				\
		src/hud.c 				\
		src/ennemy.c 			\
		src/game_tools.c 		\
		src/mlx_tools.c 		\
		main.c
		

INCL = header/

HEADER = $(INCL)

CC = gcc

LIBFT = libft/libft.a

CFLAGS = -O3 -Wall -Werror -g3 -flto -march=native

FRMWORKS = -framework AppKit -framework OpenGL

LIBLINK = -L ./minilibx_opengl_20191021/ -lmlx $(FRMWORKS)

LIB = libft/

OBJS = ${SRCS:.c=.o}

all : $(NAME)

.c.o:
	${CC} ${CFLAGS} -I $(HEADER) -c $< -o ${<:.c=.o}

libft :
	@$(MAKE) -C libft

$(NAME): bonusclear libft $(OBJS) $(HEADER)
	gcc -I $(HEADER) $(OBJS) libft/libft.a libmlx_Linux.a  -lm -lX11 -lXext -o cube3D

rebonus : fclean bonus

bonus : libft $(HEADER)
	${CC} ${CFLAGS} -D BONUS -I $(HEADER) -c ${SRCS}
	gcc -I $(HEADER) *.o libft/libft.a libmlx_Linux.a -lm -lX11 -lXext -o cube3D

bnsobjs : 
	${CC} ${CFLAGS} -D BONUS -I $(HEADER) -c ${SRCS} -o SRCS/

cleanlibft :
	$(MAKE) -C libft clean

fcleanlibft :
	$(MAKE) -C libft fclean

bonusclear :
	rm -rf *.o
clean : cleanlibft
	$(RM) $(OBJS)

fclean : clean fcleanlibft
	$(RM) $(NAME)
	rm -rf a.out a.out.dSYM
	rm -rf *.o

re : fclean all

.PHONY : all clean fclean re libft cleanlibft fcleanlibft bonus
