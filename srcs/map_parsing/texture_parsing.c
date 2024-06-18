/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:33:57 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/19 00:17:21 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_texture_paths(char **texture_path, char *line)
{
	char	*trimmed_line;

	trimmed_line = line;
	while (ft_isspace(*trimmed_line))
		trimmed_line++;
	*texture_path = ft_strdup(trimmed_line);
}

int	compare_textures(t_texture *texture, char *line)
{
	int	status;

	status = 0;
	if (!ft_strncmp(line, "NO ", 3))
	{
		fill_texture_paths(&(texture->n_path), line + 3);
		status = check_path(texture->n_path);
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		fill_texture_paths(&(texture->e_path), line + 3);
		status = check_path(texture->e_path);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		fill_texture_paths(&(texture->s_path), line + 3);
		status = check_path(texture->s_path);
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		fill_texture_paths(&(texture->w_path), line + 3);
		status = check_path(texture->w_path);
	}
	return (status);
}

int	parse_textures(char *line, t_texture *texture)
{
	int	status;

	status = 0;
	if ((!texture->e_path || !texture->w_path || !texture->s_path
			|| !texture->n_path) && *line)
		status = compare_textures(texture, line);
	if (!line)
	{
		printf("Error\nInvalid filestop at texture readin");
		status = 1;
	}
	return (status);
}

int	dup_door_path(char *line, int *keep_read, t_texture *txt)
{
	int	status;

	status = 0;
	if (!line)
		*keep_read = 0;
	else if (ft_strlen(line) > 0 && !ft_strncmp(line, "DO ", 3))
	{
		fill_texture_paths(&(txt->d_path), line + 3);
		status = check_path(txt->d_path);
		*keep_read = 0;
	}
	return (status);
}

void	parse_door_text(char *file, t_texture *texture)
{
	int		fd;
	char	*line;
	int		keep_reading;
	int		status;

	status = 0;
	line = NULL;
	keep_reading = 1;
	fd = open_file(file);
	if (!fd)
		exit(1);
	while (keep_reading && !status)
	{
		line = get_cut_next_line(fd);
		status = dup_door_path(line, &keep_reading, texture);
		free(line);
		line = NULL;
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
	close(fd);
}
