CC=cc
CC_FLAGS=-Wall -Wextra -Werror
MLX_FLAGS=-Lminilibx-linux -lmlx_Linux -lX11 -lXext
NAME=cub3d
INC_DIR=include
SRC_DIR=src
SRC_FILES=main.c parser_elements.c
LIBFT_DIR=libft
LIBFT=$(LIBFT_DIR)/libft.a
MINILIBX_DIR=minilibx-linux
MINILIBX=$(MINILIBX_DIR)/libmlx_Linux.a
SRCS=$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS=$(SRCS:.c=.o)

all: $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(CC_FLAGS) -o $(NAME) -g $(OBJS) $(LIBFT) $(MLX_FLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MINILIBX):
	make -C $(MINILIBX_DIR)

.c.o:
	$(CC) $(CC_FLAGS) -g -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MINILIBX_DIR) clean
	rm -f $(OBJS) $(BONUS_OBJS) $(MINILIBX)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f $(EXEC_NAME)

re: fclean all

.PHONY: all clean fclean re
