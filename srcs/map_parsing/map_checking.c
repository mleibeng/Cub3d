/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvinleibenguth <marvinleibenguth@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 00:57:13 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/18 05:42:24 by marvinleibe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_line(char *line, t_line_struct *line_sort, int *map_started)
{
	if (ft_strlen(line) > 0)
	{
		if (*map_started)
			parse_map(line, line_sort->map, line_sort->rows_cols,
				line_sort->texture);
		else if ((!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
			&& !(*map_started))
			parse_floor_ceiling(line, line_sort->texture, *(line_sort->map));
		else if (is_texture_line(line) && !(*map_started))
			parse_textures(line, line_sort->texture, *(line_sort->map));
		else if (is_map_line(line) && !(*map_started))
		{
			*map_started = 1;
			parse_map(line, line_sort->map, line_sort->rows_cols,
				line_sort->texture);
		}
	}
	else if (*map_started)
	{
		printf("Error\n");
		printf("Empty line inside the map\n");
		emergency_exit(NULL, line_sort->texture, *(line_sort->map));
	}
}

void	read_lines_until_end(int fd, t_line_struct *line_sort, int *map_started)
{
	char	*line;
	int		keep_reading;

	keep_reading = 1;
	while (keep_reading)
	{
		line = get_cut_next_line(fd);
		if (!line)
			keep_reading = 0;
		else
			parse_line(line, line_sort, map_started);
	}
	if(line)
	{
		free(line);
		line = NULL;
	}
	return ;
}

void	emergency_exit_unfilled_textures_or_colors(t_texture *texture,
		char **map)
{
	printf("Error\n");
	printf("Unfilled textures or colors\n");
	emergency_exit(NULL, texture, map);
}

void	parse_file(int fd, t_texture *texture, char ***map, t_vec *rows_cols)
{
	t_line_struct	line_sort;
	int				map_started;

	line_sort.map = map;
	line_sort.rows_cols = rows_cols;
	line_sort.texture = texture;
	map_started = 0;
	read_lines_until_end(fd, &line_sort, &map_started);
	if (rows_cols->y > 0)
		(*map)[rows_cols->y] = NULL;
	if (!are_textures_and_colors_filled(texture))
		emergency_exit_unfilled_textures_or_colors(texture, *map);
}
