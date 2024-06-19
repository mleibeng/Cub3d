/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:35:47 by mleibeng          #+#    #+#             */
/*   Updated: 2024/04/23 20:17:52 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define OPERATORS "|&;()<>\\="

# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "print_functions/ft_printf/ft_printf.h"
# include "print_functions/get_next_line/get_next_line.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_issign(int c);
int					ft_isspace(int c);
int					ft_isquote(char c);
size_t				ft_strlen(const char *s);
void				*ft_memset(void *b, int c, size_t size);
void				ft_bzero(void *b, size_t size);
void				*ft_memcpy(void *dest, const void *src, size_t size);
void				*ft_memmove(void *dest, const void *src, size_t size);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t size);
void				*ft_memchr(const void *b, int c, size_t size);
int					ft_memcmp(const void *a1, const void *a2, size_t size);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t size);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t num_elements, size_t element_size);
char				*ft_strdup(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				**ft_split_delims(char const *s, char *delimiters);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
int					ft_putchar_fd(char c, int fd);
int					ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
int					ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
size_t				ft_strcspn(const char *str, const char *delimiter);
char				*ft_strtok(char *in, const char *delimiters);
size_t				ft_substr_len(const char *str, const char *c);
size_t				split_arr_len(const char *s, const char *c);
void				*ft_free(char **split_arr, size_t i);
char				*ft_strncpy(char *dest, const char *src, size_t size);
char				*ft_strncat(char *dest, const char *src, size_t size);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strcat(char *dest, const char *src);
void				*ft_memalloc(size_t size);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_strdel(char **as);
char				*ft_strnew(size_t size);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strndup(const char *s1, int len);
char				**ft_split_quotes(char *str);
int					ft_isspecialchar(char c);
size_t				ft_strspn(const char *str1, const char *str2);
char				*ft_strpbrk(const char *str1, const char *str2);
char				*ft_strtok_r(char *str, const char *delim, char **save_ptr);
void				*ft_realloc(void *ptr, size_t size);
int					ft_isoperator(char c);
int					ft_fprintf(int fd, const char *format, ...);
char				*ft_strjoin_free(char *new_var, char *value, int i);
int					ft_snprintf(char *str, int size, const char *format, ...);
int					ft_strtoi(const char *str, char **end);
const char			*ft_strtolower(char *str);

#endif