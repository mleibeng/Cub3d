CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libft.a
HEADER = libft.h
FT_PRINTF_HEADER = print_functions/ft_printf/ft_printf.h
GET_NEXT_LINE_HEADER = print_functions/get_next_line/get_next_line.h
SRCS_DIR = conversion list_functions memory_manipulation print_functions string_checks string_manipulation
SRCS = conversion/ft_atoi.c conversion/ft_itoa.c conversion/ft_tolower.c conversion/ft_toupper.c list_functions/ft_lstadd_back.c list_functions/ft_lstadd_front.c list_functions/ft_lstclear.c list_functions/ft_lstdelone.c list_functions/ft_lstiter.c list_functions/ft_lstlast.c list_functions/ft_lstmap.c list_functions/ft_lstnew.c list_functions/ft_lstsize.c memory_manipulation/ft_bzero.c memory_manipulation/ft_calloc.c memory_manipulation/ft_memchr.c memory_manipulation/ft_memcmp.c memory_manipulation/ft_memcpy.c memory_manipulation/ft_memmove.c memory_manipulation/ft_memset.c print_functions/ft_printf/ft_printf.c print_functions/ft_printf/ft_prn_hex.c print_functions/ft_printf/ft_prn_nbr.c print_functions/ft_printf/ft_prn_ptr.c print_functions/ft_printf/ft_prn_str.c print_functions/ft_printf/ft_prn_unbr.c print_functions/get_next_line/get_next_line_utils.c print_functions/get_next_line/get_next_line.c print_functions/ft_putchar_fd.c print_functions/ft_putendl_fd.c print_functions/ft_putnbr_fd.c print_functions/ft_putstr_fd.c string_checks/ft_isalnum.c string_checks/ft_isalpha.c string_checks/ft_isascii.c string_checks/ft_isdigit.c string_checks/ft_isprint.c string_checks/ft_issign.c string_checks/ft_iswhitespace.c string_manipulation/ft_split.c string_manipulation/ft_strchr.c string_manipulation/ft_strdup.c string_manipulation/ft_striteri.c string_manipulation/ft_strjoin.c string_manipulation/ft_strlcat.c string_manipulation/ft_strlcpy.c string_checks/ft_strlen.c string_manipulation/ft_strmapi.c string_manipulation/ft_strncmp.c string_manipulation/ft_strnstr.c string_manipulation/ft_strrchr.c string_manipulation/ft_strtrim.c string_manipulation/ft_substr.c string_manipulation/ft_split_delims.c string_manipulation/ft_strtok.c string_manipulation/ft_strcspn.c string_checks/ft_isquote.c string_manipulation/ft_strcat.c string_manipulation/ft_strcpy.c string_manipulation/ft_strncat.c string_manipulation/ft_strncpy.c string_manipulation/ft_strdel.c string_manipulation/ft_strnew.c string_manipulation/ft_strsub.c string_checks/ft_strcmp.c memory_manipulation/ft_memalloc.c string_manipulation/ft_strndup.c string_manipulation/ft_split_quotes.c string_checks/ft_isspecialchar.c string_manipulation/ft_strspn.c string_manipulation/ft_strpbrk.c string_manipulation/ft_strtok_r.c memory_manipulation/ft_realloc.c string_checks/ft_isoperator.c print_functions/ft_printf/ft_fprintf.c string_manipulation/ft_strjoin_free.c print_functions/ft_printf/ft_snprintf.c conversion/ft_strtoi.c print_functions/ft_printf/custom_ft_itoa.c print_functions/ft_printf/custom_handles.c conversion/ft_strtolower.c print_functions/get_next_line/get_cut_next_line.c

OBJS = $(SRCS:.c=.o)

COLOR_RESET			=	\033[0m
COLOR_CYAN			=	\033[36m
COLOR_GREEN			=	\033[32m
COLOR_RED			=	\033[31m

all: $(NAME)

$(NAME): display_message $(OBJS)
	@ar rcs $@ $(OBJS)

display_message:
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),fclean)
ifneq ($(MAKECMDGOALS),re)
	@if [ -f $(NAME) ] && [ -n "$(OBJS)" ]; then \
			echo "$(COLOR_CYAN)Nothing to be done for all$(COLOR_RESET)"; \
	else \
			echo "$(COLOR_CYAN)Compilation will now begin...$(COLOR_RESET)"; \
	fi
endif
endif
endif

%.o: %.c $(HEADER) $(FT_PRINTF_HEADER) $(GET_NEXT_LINE_HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re