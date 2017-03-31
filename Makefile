# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/04 18:49:05 by bsouchet          #+#    #+#              #
#    Updated: 2017/03/31 19:38:05 by gmonein          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = clang

NAME = fractal

FLAGS = -O3 -lpthread

LIBFT = libft

DIR_S = sources

DIR_O = temporary

DIR_MLX = mlx/minilibx_sierra

DIR_MLX_X11 = mlx/minilibx_X11

HEADERS = includes

SOURCES = fractal.c \
		  init.c \
		  key_hook.c \
		  main.c \
		  misc.c \
		  mouse_hook.c \
		  thread.c \
		  mini_frac.c \
		  color.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: temporary $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@make -C $(DIR_MLX)
	@$(CC) $(FLAGS) -L $(LIBFT) -lft -o $@ $^ -framework OpenGL -framework AppKit -L $(DIR_MLX) -lmlx

X11: temporary $(OBJS)
	@make -C $(LIBFT)
	$(CC) $(FLAGS) -o $(NAME) -L $(LIBFT) $(OBJS) mlx/minilibx_X11/libmlx.a -lm -lXext -lX11

temporary:
	@mkdir -p temporary

$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADERS)/$(NAME).h
	@$(CC) $(FLAGS) -I $(HEADERS) -c -o $@ $<

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFT)
	@make clean -C $(DIR_MLX)
	@rm -rf $(DIR_O)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@make fclean -C $(DIR_MLX)

re: fclean all

.PHONY: all X11
