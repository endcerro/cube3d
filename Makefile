# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/18 17:54:38 by edal--ce          #+#    #+#              #
#    Updated: 2020/02/04 05:54:39 by edal--ce         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out

SRCS = 	src/fonctions.c \
		src/map.c 		\
		src/keys.c 		\
		src/dda.c 		\
		src/screenshot.c \
		src/cub_loader.c \
		main.c
		

INCL = header/

HEADER = $(INCL)header.h

CC = gcc

LIBFT = libft/libft.a

CFLAGS = #-g3 -fsanitize=address#-Wpadded #-Wall -Wextra -Wpadded 

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
