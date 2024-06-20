/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:33:57 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/20 03:00:27 by fkeitel          ###   ########.fr       */
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

int	dup_door_path(char *line, t_texture *txt)
{
	int	status;

	status = 0;
	if (ft_strlen(line) > 0 && !ft_strncmp(line, "DO ", 3))
	{
		fill_texture_paths(&(txt->d_path), line + 3);
		status = check_path(txt->d_path);
	}
	return (status);
}

int	door_text_loop(int fd, char *line, t_texture *texture)
{
	int	status;
	int	keep_reading;
	int	final_status;

	status = 0;
	keep_reading = 1;
	final_status = 0;
	while (keep_reading)
	{
		line = get_cut_next_line(fd);
		if (status)
			final_status = 1;
		if (!line)
			keep_reading = 0;
		else if (ft_strlen(line) < MAX_LINE_LENGTH)
			status = dup_door_path(line, texture);
		else
			status = 1;
		free(line);
		line = NULL;
	}
	return (final_status);
}
