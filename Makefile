# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/18 17:54:38 by edal--ce          #+#    #+#              #
#    Updated: 2020/02/28 10:21:54 by edal--ce         ###   ########.fr        #
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
		src/other_functions.c \
		src/start_pos.c \
		src/load_utils.c \
		src/mouse.c 	\
		src/init.c 	\
		src/menu.c 	\
		src/hud.c \
		src/ennemy.c \
		src/game_tools.c \
		src/mlx_tools.c \
		main.c
		

INCL = header/

HEADER = $(INCL)

CC = gcc

LIBFT = libft/libft.a

CFLAGS = -O3 -Wall -Wextra -g3 -flto -march=native

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
	gcc -I $(HEADER) $(OBJS) libft/libft.a libmlx_Linux.a  -lm -lX11 -lXext  #-I minilibx/ $(OBJS) 

test : libft $(OBJS)
	

rebonus : fclean bonus

bonus : libft $(HEADER) #$(BNSOBJS)
	${CC} ${CFLAGS} -D BONUS -I $(HEADER) -c ${SRCS}
	gcc -I $(HEADER) *.o libft/libft.a libmlx_Linux.a  -lm -lX11 -lXext 

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
