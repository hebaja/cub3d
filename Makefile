SHELL = /bin/bash

CC = cc

CFLAGS = -Wall -Wextra -Werror

MLX_FLAGS=-Lminilibx-linux -lmlx_Linux -lX11 -lXext

NAME = cub3d

SRC_DIR = src

SRC_FILES = main.c parser_file_1.c parser_file_2.c\
			file_utils.c st_file_utils.c parser_file_utils.c\
			clean_utils.c valid_map1.c valid_map2.c\
			put_error.c color_elem_utils.c texture_elem_utils.c\
			st_mlx_utils.c ray_cast.c st_coord_utils.c\
			mlx_draw.c mlx_hook_utils.c

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

MINILIBX_DIR = minilibx-linux

MINILIBX = $(MINILIBX_DIR)/libmlx_Linux.a

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	@clear
	@$(CC) $(CFLAGS) -o $(NAME) -g $(OBJS) $(LIBFT) $(MLX_FLAGS)
	@echo -n "  Compiling"
	@$(MAKE) -s loading
	@clear
	@echo -e "\033[32m ✓ \033[0m Compilation successful!"

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MINILIBX):
	@make -C $(MINILIBX_DIR)

.c.o:
	@$(CC) $(CFLAGS) -g -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MINILIBX_DIR) clean
	rm -f $(OBJS) $(MINILIBX)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	@clear
	@echo -n "  Cleaning"
	@$(MAKE) -s loading
	@rm -f $(NAME)
	@echo -e "\033[32m ✓ \033[0m Clean complete!"

re: fclean all

loading:
	@spin=("⠁" "⠃" "⠇" "⠧" "⠷" "⠿" "⠷" "⠧" "⠇" "⠃"); \
	for i in {1..1}; do \
		for j in $${spin[@]}; do \
			echo -ne "$$j\r"; \
			sleep 0.1; \
		done; \
	done

.PHONY:	all clean fclean re
