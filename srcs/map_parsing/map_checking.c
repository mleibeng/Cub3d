/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 00:57:13 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/18 01:13:08 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_texture_line(char *line)
{
	return (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3));
}

int	are_textures_filled(t_texture *texture)
{
	return (texture->n_path != NULL && texture->s_path != NULL
		&& texture->w_path != NULL && texture->e_path != NULL);
}

int	are_colors_filled(t_texture *texture)
{
	return (texture->floor[0] != -1 && texture->skybox[0] != -1);
}

void	parse_line(char *line, t_texture *texture, char ***map,
		t_vec *rows_cols, int *map_started)
{
	if (ft_strlen(line) > 0)
	{
		if (*map_started)
			parse_map(line, map, rows_cols, texture);
		else if ((!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
			&& !(*map_started))
			parse_floor_ceiling(line, texture, *map);
		else if (is_texture_line(line) && !(*map_started))
			parse_textures(line, texture, *map);
		else if (is_map_line(line) && !(*map_started))
		{
			*map_started = 1;
			parse_map(line, map, rows_cols, texture);
		}
	}
	else if (*map_started)
	{
		printf("Error\n");
		printf("Empty line inside the map\n");
		emergency_exit(NULL, texture, *map);
	}
}

void	parse_file(int fd, t_texture *texture, char ***map, t_vec *rows_cols)
{
	char	*line;
	int		keep_reading;
	int		map_started;

	keep_reading = 1;
	map_started = 0;
	while (keep_reading)
	{
		line = get_cut_next_line(fd);
		if (!line)
			keep_reading = 0;
		else
		{
			parse_line(line, texture, map, rows_cols, &map_started);
			free(line);
		}
	}
	if (rows_cols->y > 0)
		(*map)[rows_cols->y] = NULL;
	if (!are_textures_filled(texture) || !are_colors_filled(texture))
	{
		printf("Error\n");
		printf("Unfilled textures or colors\n");
		emergency_exit(NULL, texture, *map);
	}
}
