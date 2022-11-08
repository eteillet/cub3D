# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/07 15:37:26 by eteillet          #+#    #+#              #
#    Updated: 2021/01/07 15:37:46 by eteillet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

HEADERS		= ./inc/cub3d.h \
			  ./inc/constants.h \
			  ./inc/structures.h

SRCS		= ./src/cub3d.c \
			  ./src/check_and_parse/check_filename.c \
			  ./src/check_and_parse/check_surrounded_map.c \
			  ./src/check_and_parse/parser.c \
			  ./src/check_and_parse/parse_color.c \
			  ./src/check_and_parse/parse_map.c \
			  ./src/check_and_parse/parse_map_utils1.c \
			  ./src/check_and_parse/parse_map_utils2.c \
			  ./src/check_and_parse/parse_player.c \
			  ./src/check_and_parse/parse_resolution.c \
			  ./src/check_and_parse/parse_sprite.c \
			  ./src/check_and_parse/parse_texture.c \
			  ./src/events/key_event.c \
			  ./src/events/movement_camera.c \
			  ./src/events/movement_player.c \
			  ./src/game/bitmap.c \
			  ./src/game/dda.c \
			  ./src/game/draw_image.c \
			  ./src/game/raycasting.c \
			  ./src/game/sprite_display.c \
			  ./src/game/sprite_store_and_sort.c \
			  ./src/game/texture.c \
			  ./src/utils/free.c \
			  ./src/utils/get_next_line.c \
			  ./src/utils/init1.c \
			  ./src/utils/init2.c \
			  ./src/utils/utils1.c \
			  ./src/utils/utils2.c


SRCS_BONUS	= ./src/game/hud.c \
			  ./src/game/minimap.c

OBJS		= ${SRCS:.c=.o}
OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

RM			= rm -f

CFLAGS		= -Wall -Werror -Wextra

CC			= gcc

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS} ${OBJS_BONUS}
	cd libft && make bonus
	cd minilibx-linux && make && ./configure
	${CC} ${CFLAGS} ${OBJS} ${OBJS_BONUS} -o ${NAME} minilibx-linux/libmlx.a -lbsd -lXext -lX11 -lm  libft/libft.a

bonus:		${NAME}
	
clean:
	cd minilibx-linux && make clean
	cd libft && make clean
	${RM} ${OBJS} ${OBJS_BONUS}

fclean:		clean
	cd libft && make fclean
	${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus