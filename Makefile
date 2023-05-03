# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 14:53:15 by yboudoui          #+#    #+#              #
#    Updated: 2023/05/03 20:17:17 by kdhrif           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	cub3D

CC					=	cc

CFLAGS				=	-Wall -Wextra -Werror -Ofast -flto -march=native

RM					=	rm -f

MLX_DIR				=	mlx_linux

LINK				=	-L $(MLX_DIR) -lmlx_Linux -lmlx -lXext -lX11 -lm


# **************************************************************************** #

SRCS	=\
./utils/str/ft_strtrim.c\
./utils/str/ft_strncmp.c\
./utils/str/ft_strlen.c\
./utils/str/ft_substr.c\
./utils/str/ft_split.c\
./utils/str/ft_putstr_fd.c\
./utils/str/ft_isalpha.c\
./utils/str/ft_isalnum.c\
./utils/str/ft_is_space_nl_comma.c\
./utils/str/ft_strdup.c\
./utils/str/ft_atoi.c\
./utils/lst/source/ft_lst_remove_one.c\
./utils/lst/source/ft_lstclear.c\
./utils/lst/source/ft_lstmap.c\
./utils/lst/source/add.c\
./utils/lst/source/create.c\
./utils/lst/source/ft_lstlast.c\
./utils/is_charset/is_charset.c\
./utils/atoi_to.c\
./utils/file/file.c\
./utils/memory/ft_memcpy.c\
./utils/memory/ft_calloc.c\
./utils/memory/ft_memset.c\
./utils/int_array/int_array.c\
./utils/get_next_line/get_next_line_utils.c\
./utils/get_next_line/get_next_line.c\
./main.c\
./mlx_utils/color/color.c\
./mlx_utils/vec2/vec2.c\
./mlx_utils/vec2/vec2f.c\
./mlx_utils/event/window/window.c\
./mlx_utils/event/event.c\
./mlx_utils/event/keyboard/keyboard.c\
./mlx_utils/event/mouse/mouse.c\
./mlx_utils/line/line.c\
./mlx_utils/pixel/pixel.c\
./mlx_utils/screen/screen.c\
./mlx_utils/mlx_utils.c\
./mlx_utils/image/quad.c\
./mlx_utils/image/triangle.c\
./mlx_utils/image/image.c\
./mlx_utils/image/line.c\
./dda.c\
./draw/event_state.c\
./draw/draw.c\
./parsing/ft_error.c\
./parsing/parsing.c\
./parsing/ft_texture_utils.c\
./parsing/ft_texture_parsing.c\
./parsing/ft_colors_parsing.c\
./parsing/parsing_debug.c\

INCS	=\
./utils/str\
./utils/lst/include\
./utils/is_charset\
./utils\
./utils/file\
./utils/memory\
./utils/int_array\
./utils/get_next_line\
.\
./mlx_linux\
./mlx_linux\
./mlx_utils/color\
./mlx_utils/vec2\
./mlx_utils/event\
./mlx_utils/event/window\
./mlx_utils/event/keyboard\
./mlx_utils/event/mouse\
./mlx_utils/line\
./mlx_utils/pixel\
./mlx_utils/screen\
./mlx_utils\
./mlx_utils/image\
./parsing\

# **************************************************************************** #

OBJS		=	$(SRCS:.c=.o)

all:		$(NAME)

$(OBJS): %.o : %.c
		@$(CC) $(CFLAGS)										\
		$(addprefix -I , $(INCS)) -I $(MLX_DIR)	\
		-c $<\
		-o $(<:.c=.o)
		@echo $(CC) $(CFLAGS) $@

$(NAME):	$(OBJS)
			@$(MAKE) -si all -C $(MLX_DIR)
			@$(CC) $(CFLAGS) $(OBJS) $(LINK) -o $(NAME)
			@echo $(CC) $(CFLAGS) $(NAME)

clean:
			@$(MAKE) -si clean -C $(MLX_DIR)
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

valgrind:	CFLAGS+= -g3
valgrind:	re
			@valgrind														\
			-q																\
			--leak-check=full												\
			--show-leak-kinds=all											\
			--track-origins=yes												\
			./$(NAME)														\

.PHONY:		all clean fclean re bonus
