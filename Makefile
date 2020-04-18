# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/18 17:54:38 by edal--ce          #+#    #+#              #
#    Updated: 2020/04/18 15:21:52 by edal--ce         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

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
		src/mlx_tools.c 		


INCL = header/

HEADER = $(INCL)

CC = gcc

LIBFT = libft/libft.a

CFLAGS = -O3 -Wall -Wextra -g3 -flto -march=native #-fsanitize=address

FRMWORKS = -framework AppKit -framework OpenGL

LIBLINK = -L ./minilibx_opengl_20191021/ -lmlx $(FRMWORKS)

LIB = libft/

OBJS = ${SRCS:.c=.o}


all : $(NAME) ec_cs

main : ec_main
	@${CC} ${CFLAGS} -I $(HEADER) -c main.c

b_main : ec_main
	@${CC} ${CFLAGS} -D BONUS -I $(HEADER) -c main.c 

.c.o: 
	@${CC} ${CFLAGS} -I $(HEADER) -c $< -o ${<:.c=.o}

libft :
	@$(MAKE) -C libft

mlx :
	@$(MAKE) -C mlx

$(NAME): libft ec_srcs $(OBJS) ec_srgg ec_main main ec_maingg $(HEADER)
	@${CC} -I $(HEADER) $(OBJS) main.o libft/libft.a mlx/libmlx_Linux.a -lm -lX11 -lXext -lbsd -o $(NAME)

bonus : libft ec_srcs $(OBJS) ec_srgg ec_main b_main ec_maingg $(HEADER)
	@${CC} -I $(HEADER) $(OBJS) main.o libft/libft.a mlx/libmlx_Linux.a -lm -lX11 -lXext -lbsd -o $(NAME)
	@echo "\e[124;31mBonus build succes, ready to run \e[0m"
	
cleanlibft :
	$(MAKE) -C libft clean

fcleanlibft :
	$(MAKE) -C libft fclean

clean : cleanlibft
	$(RM) $(OBJS)
	$(RM) -rf main.o

fclean : clean fcleanlibft
	$(RM) $(NAME)

re : fclean all

ec_srcs : 
	@echo "\033[33mBuilding sources...\e[0m"

ec_srgg : 
	@echo "\033[32mBuild succes\e[0m"

ec_main :
	@echo "\033[33mBuilding main\e[0m"

ec_maingg :
	@echo "\033[32mBuild succes\e[0m"

ec_cs :
	@echo "\e[124;31mBuild succes, ready to run \e[0m"

.PHONY : all clean fclean re libft cleanlibft fcleanlibft bonus
