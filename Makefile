# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 14:26:27 by fkeitel           #+#    #+#              #
#    Updated: 2024/06/19 19:18:05 by mleibeng         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3d
BONUS_NAME := cub3d_bonus
CFLAGS := -Wall -Wextra -Werror -Wunreachable-code -Ofast -g
LIBMLX := ./MLX42
LIBMLX_URL := https://github.com/codam-coding-college/MLX42.git
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
HEADERS := -I ./include -I $(LIBMLX)/include
BONUS_HEADER := -I ./include_bonus -I$(LIBMLX)/include

# Directories
SRC_DIR := srcs
SRC_BONUS_DIR := srcs_bonus
OBJ_DIR := obj

LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -L$(LIBFT_DIR) -lft
SRCS := srcs/calculations/calculations.c srcs/calculations/line_algorithm.c srcs/calculations/math.c srcs/calculations/player_calculations.c srcs/calculations/ray_algorithm.c \
	srcs/init_functions/ini_weap_anims.c srcs/init_functions/init_imgs.c srcs/init_functions/init.c srcs/init_functions/manual.c srcs/map_parsing/bounds_checking.c \
	srcs/map_parsing/color_parsing.c srcs/map_parsing/door_validation.c srcs/map_parsing/error_messages.c srcs/map_parsing/fill_and_line_checks.c srcs/map_parsing/free_functions.c \
	srcs/map_parsing/map_checking.c srcs/map_parsing/map_filling.c srcs/map_parsing/map_parsing.c srcs/map_parsing/map_validation.c srcs/map_parsing/parser.c srcs/map_parsing/texture_parsing.c \
	srcs/rendering/color_functions.c srcs/rendering/compas.c srcs/rendering/minimap_calcs.c srcs/rendering/minimap.c srcs/rendering/rendering.c srcs/rendering/replace_image.c srcs/rendering/weapon.c \
	srcs/user_input/door_logic.c srcs/user_input/key_input.c srcs/user_input/mouse_input.c srcs/user_input/player_move.c srcs/user_input/user_input.c srcs/debugging.c srcs/main.c
BONUS_SRCS := $(shell find $(SRC_BONUS_DIR) -name '*.c')

OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
BONUS_OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(BONUS_SRCS))

all: $(LIBFT) libmlx $(NAME)
	@chmod 000 manual.txt
	@echo "$(NAME) successfully built!"

libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
			git clone $(LIBMLX_URL) $(LIBMLX); \
	fi
	@cmake -S $(LIBMLX) -B $(LIBMLX)/build
	@cmake --build $(LIBMLX)/build --parallel 4

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Ensure the obj directory and necessary subdirectories are created
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

bonus: $(LIBFT) libmlx $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	@$(CC) $(BONUS_OBJS) $(LIBS) $(BONUS_HEADERS) -o $(BONUS_NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBMLX)/build
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -rf $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@chmod 777 manual.txt

re: fclean all

mlxfclean: fclean
	@rm -rf $(LIBMLX)

.PHONY: all clean fclean re libmlx bonus
