/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:33:57 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/18 00:03:46 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_texture_paths(char **texture_path, char *line)
{
	while (ft_isspace(*line))
		line++;
	*texture_path = ft_strdup(line);
}

void	compare_textures(t_texture *texture, char *line, char **map)
{
	if (!ft_strncmp(line, "NO ", 3))
	{
		fill_texture_paths(&(texture->n_path), line + 3);
		check_path(texture->n_path, texture, map);
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		fill_texture_paths(&(texture->e_path), line + 3);
		check_path(texture->e_path, texture, map);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		fill_texture_paths(&(texture->s_path), line + 3);
		check_path(texture->s_path, texture, map);
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		fill_texture_paths(&(texture->w_path), line + 3);
		check_path(texture->w_path, texture, map);
	}
}

void	parse_textures(char *line, t_texture *texture, char **map)
{
	if ((!texture->e_path || !texture->w_path || !texture->s_path
			|| !texture->n_path) && *line)
		compare_textures(texture, line, map);
	if (!line)
	{
		printf("Error\n");
		printf("invalid filestop at texture readin");
		emergency_exit(NULL, texture, NULL);
	}
}

void	dup_door_path(char *line, int *keep_read, t_texture *txt, char **map)
{
	if (!line)
		*keep_read = 0;
	else if (ft_strlen(line) > 0 && !ft_strncmp(line, "DO ", 3))
	{
		fill_texture_paths(&(txt->d_path), line + 3);
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
		printf("Error\n");
		printf("Error reopening file");
		emergency_exit(NULL, texture, map);
	}
	while (keep_reading)
	{
		line = get_cut_next_line(fd);
		dup_door_path(line, &keep_reading, texture, map);
	}
	close(fd);
}
