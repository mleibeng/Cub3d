NAME := cub3d
BONUS_NAME := cub3d_bonus
CFLAGS := -Wall -Wextra -Werror -Wunreachable-code -Ofast
LIBMLX := ./MLX42
LIBMLX_URL := https://github.com/codam-coding-college/MLX42.git
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
HEADERS := -I ./include -I $(LIBMLX)/include
LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -L$(LIBFT_DIR) -lft
SRCS :=
BONUS_SRCS :=
OBJS := $(SRCS:.c=.o)
BONUS_OBJS := $(BONUS_SRCS:.c=.o)

all: $(LIBFT) libmlx $(NAME)

libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
			git clone $(LIBMLX_URL) $(LIBMLX); \
	fi
	@cmake $(LIBMLX) -H $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

bonus: $(LIBFT) libmlx $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	@$(CC) $(BONUS_OBJS) $(LIBS) $(HEADERS) -o $(BONUS_NAME)

clean:
	@rm -rf $(OBJS) $(BONUS_OBJS)
	@rm -rf $(LIBMLX)/build
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -rf $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

mlxfclean: fclean
	@rm -rf $(LIBMLX)

.PHONY: all clean fclean re libmlx bonus