/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:33:57 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/17 13:16:50 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	*init_texture(void)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		emergency_exit(NULL, NULL, NULL);
	_init_texture(texture);
	return (texture);
}

void	check_path(char *path, t_texture *text, char **map)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening texture file");
		emergency_exit(NULL, text, map);
	}
	close(fd);
	return ;
}

void	compare_textures(t_texture *texture, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
	{
		texture->n_path = ft_strdup(line + 3);
		check_path(texture->n_path, texture, NULL);
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		texture->w_path = ft_strdup(line + 3);
		check_path(texture->w_path, texture, NULL);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		texture->s_path = ft_strdup(line + 3);
		check_path(texture->s_path, texture, NULL);
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		texture->e_path = ft_strdup(line + 3);
		check_path(texture->e_path, texture, NULL);
	}
}

void	parse_textures(int fd, t_texture *texture)
{
	char	*line;
	int		keep_reading;

	line = NULL;
	keep_reading = 1;
	while (keep_reading && (!texture->e_path || !texture->w_path
			|| !texture->s_path || !texture->n_path))
	{
		line = get_cut_next_line(fd);
		if (!line)
			keep_reading = 0;
		else
		{
			if (ft_strlen(line) > 0)
				compare_textures(texture, line);
			free(line);
		}
	}
	if (!line)
	{
		perror("invalid filestop at texture readin");
		emergency_exit(NULL, texture, NULL);
	}
}

void	dup_door_path(char *line, int *keep_read, t_texture *txt, char **map)
{
	if (!line)
		*keep_read = 0;
	else if (ft_strlen(line) > 0 && !ft_strncmp(line, "DO ", 3))
	{
		txt->d_path = ft_strdup(line + 3);
		free(line);
		check_path(txt->d_path, txt, map);
		*keep_read = 0;
	}
	else
		free(line);
}

void	parse_door_text(char *file, t_texture *texture, char **map)
{
	int		fd;
	char	*line;
	int		keep_reading;

	line = NULL;
	keep_reading = 1;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error reopening file");
		emergency_exit(NULL, texture, map);
	}
	while (keep_reading)
	{
		line = get_cut_next_line(fd);
		dup_door_path(line, &keep_reading, texture, map);
	}
	close(fd);
}
