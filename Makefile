SHELL = /bin/bash

CC = cc

CFLAGS = -Wall -Wextra -Werror

BONUS_CFLAGS = -Wall -Wextra -Werror -DBONUS

MLX_FLAGS=-Lminilibx-linux -lmlx_Linux -lX11 -lXext

NAME = cub3d

SRC_DIR = src

OBJ_DIR = obj

SRC_MAIN_DIR = $(SRC_DIR)/main

SRC_COMMON_DIR = $(SRC_DIR)/common

SRC_BONUS_DIR = $(SRC_DIR)/bonus

OBJ_MAIN_DIR = $(OBJ_DIR)/main

OBJ_COMMON_DIR = $(OBJ_DIR)/common

OBJ_BONUS_DIR = $(OBJ_DIR)/bonus

SRC_MAIN_FILES = main.c st_mlx_utils.c mlx_draw.c gameplay.c gameplay_utils.c prepare_game.c 

SRC_COMMON_FILES = parser_file_1.c parser_file_2.c file_utils.c\
			st_file_utils.c parser_file_utils.c clean_utils.c\
			clean_st_utils.c valid_map1.c valid_map2.c\
			put_error.c color_elem_utils.c texture_elem_utils.c\
			ray_cast.c st_coord_utils.c mlx_hook_utils.c

SRC_BONUS_FILES = main_bonus.c gameplay_bonus.c gameplay_utils_bonus.c prepare_game_bonus.c\
				st_mlx_utils_bonus.c minimap1_bonus.c minimap2_bonus.c\
				minimap3_bonus.c mlx_draw_bonus.c

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

MINILIBX_DIR = minilibx-linux

MINILIBX = $(MINILIBX_DIR)/libmlx_Linux.a

SRCS_MAIN = $(addprefix $(SRC_MAIN_DIR)/, $(SRC_MAIN_FILES))

SRCS_COMMON = $(addprefix $(SRC_COMMON_DIR)/, $(SRC_COMMON_FILES))

SRCS_BONUS = $(addprefix $(SRC_BONUS_DIR)/, $(SRC_BONUS_FILES))

OBJS_MAIN = $(addprefix $(OBJ_MAIN_DIR)/, $(notdir $(SRCS_MAIN:.c=.o)))

OBJS_COMMON = $(addprefix $(OBJ_COMMON_DIR)/, $(notdir $(SRCS_COMMON:.c=.o)))

OBJS_BONUS = $(addprefix $(OBJ_BONUS_DIR)/, $(notdir $(SRCS_BONUS:.c=.o)))

all: $(NAME)

$(NAME): $(OBJS_MAIN) $(OBJS_COMMON) $(LIBFT) $(MINILIBX)
	@clear
	@$(CC) $(CFLAGS) -o $(NAME) -g  $(OBJS_MAIN) $(OBJS_COMMON) $(LIBFT) $(MLX_FLAGS) -lm
	@echo -n "  Compiling"
	@$(MAKE) -s loading
	@clear
	@echo -e "\033[32m ✓ \033[0m Compilation successful!"

bonus: $(OBJS_BONUS) $(OBJS_COMMON) $(LIBFT) $(MINILIBX)
	@clear
	@$(CC) $(BONUS_CFLAGS) -o $(NAME) -g -DIS_BONUS $(OBJS_BONUS) $(OBJS_COMMON) $(LIBFT) $(MLX_FLAGS) -lm
	@echo -n "  Compiling bonus"
	@$(MAKE) -s loading
	@clear
	@echo -e "\033[32m ✓ \033[0m Bonus compilation successful!"

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MINILIBX):
	@make -C $(MINILIBX_DIR)

$(OBJ_MAIN_DIR)/%.o: $(SRC_MAIN_DIR)/%.c
	@mkdir -p $(OBJ_MAIN_DIR)
	@$(CC) $(CFLAGS) -g -c $< -o $@

$(OBJ_COMMON_DIR)/%.o: $(SRC_COMMON_DIR)/%.c
	@mkdir -p $(OBJ_COMMON_DIR)
	@$(CC) $(CFLAGS) -g -c $< -o $@

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	@mkdir -p $(OBJ_BONUS_DIR)
	@$(CC) $(BONUS_CFLAGS) -g -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(MINILIBX_DIR) clean
	@rm -f $(OBJS_MAIN) $(OBJS_COMMON) $(OBJS_BONUS) $(MINILIBX)
	@rm -rf $(OBJ_MAIN_DIR) $(OBJ_COMMON_DIR) $(OBJ_BONUS_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
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
