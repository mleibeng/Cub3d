/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 00:57:13 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/19 17:19:36 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_line(char *line, t_line_struct *line_sort, int *map_started)
{
	int	status;

	status = 0;
	if (ft_strlen(line) > 0)
	{
		if (*map_started)
			status = parse_map(line, line_sort->map, line_sort->rows_cols);
		else if ((!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
			&& !(*map_started))
			status = parse_floor_ceiling(line, line_sort->texture);
		else if (is_texture_line(line) && !(*map_started))
			status = parse_textures(line, line_sort->texture);
		else if (is_map_line(line) && !(*map_started))
		{
			*map_started = 1;
			status = parse_map(line, line_sort->map, line_sort->rows_cols);
		}
		return (status);
	}
	else if (*map_started)
	{
		printf("Error\nEmpty line inside the map\n");
		return (1);
	}
	return (status);
}

int	read_lines_until_end(int fd, t_line_struct *line_sort, int *map_started)
{
	char	*line;
	int		keep_reading;
	int		status;

	status = 0;
	keep_reading = 1;
	while (keep_reading)
	{
		line = get_cut_next_line(fd);
		if (!line || status)
			keep_reading = 0;
		else
			status = parse_line(line, line_sort, map_started);
		free(line);
		line = NULL;
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
	return (status);
}

void	emergency_exit_unfilled_textures_or_colors(t_texture *texture,
		char **map)
{
	printf("Error\nUnfilled textures or colors\n");
	emergency_exit(NULL, texture, map);
}

void	parse_file(int fd, t_texture *texture, char ***map, t_vec *rows_cols)
{
	t_line_struct	line_sort;
	int				map_started;

	map_started = 0;
	line_sort.map = map;
	line_sort.rows_cols = rows_cols;
	line_sort.texture = texture;
	if (read_lines_until_end(fd, &line_sort, &map_started))
	{
		close(fd);
		emergency_exit(NULL, texture, *map);
	}
	if (line_sort.rows_cols->x > 0)
		(*map)[line_sort.rows_cols->x] = NULL;
	if (line_sort.rows_cols->y > 0)
		(*map)[line_sort.rows_cols->y] = NULL;
	if (!are_textures_and_colors_filled(texture))
	{
		close(fd);
		emergency_exit_unfilled_textures_or_colors(texture, *map);
	}
}
