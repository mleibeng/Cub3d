/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 00:35:49 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/07 06:30:17 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	parse_string(t_stash_data *stash)
{
	size_t	i;

	i = 0;
	while (stash->content[i] != '\n' && stash->content[i])
		i++;
	if (stash->content[i] == '\n')
		i++;
	return (i);
}

void	*free_stash(t_stash_data *stash)
{
	free(stash->content);
	stash->content = NULL;
	stash->eof = 0;
	return (NULL);
}

int	readout(int fd, t_stash_data *stash)
{
	int		nbyte;
	char	buf[BUFFER_SIZE + 1];
	char	*temp;

	while (!stash->eof)
	{
		nbyte = read(fd, buf, BUFFER_SIZE);
		if (nbyte < 0)
			return (0);
		else if (nbyte == 0)
			stash->eof = 1;
		buf[nbyte] = '\0';
		temp = ft_strjoin(stash->content, buf);
		if (temp == NULL)
			return (0);
		if (stash->content != NULL)
			free(stash->content);
		stash->content = temp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (1);
}

char	*new_line_gen(t_stash_data *stash, size_t i)
{
	char	*new_line;
	char	*tmp;

	if (i == 0)
		return (NULL);
	new_line = (char *)malloc((i + 1) * sizeof(char));
	if (!new_line)
		return (NULL);
	new_line[i] = '\0';
	ft_memcpy(new_line, stash->content, i);
	tmp = ft_strdup(stash->content + i);
	if (tmp == NULL)
	{
		free(new_line);
		return (NULL);
	}
	free(stash->content);
	stash->content = tmp;
	return (new_line);
}

char	*get_next_line(int fd)
{
	char				*new_line;
	static t_stash_data	stash[10240];
	size_t				i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!readout(fd, &stash[fd]))
		return (free_stash(&stash[fd]));
	if (stash[fd].eof && stash[fd].content[0] == '\0')
		return (free_stash(&stash[fd]));
	i = parse_string(&stash[fd]);
	new_line = new_line_gen(&stash[fd], i);
	if (new_line == NULL)
		return (free_stash(&stash[fd]));
	return (new_line);
}
