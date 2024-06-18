/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvinleibenguth <marvinleibenguth@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 00:57:13 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/18 18:54:17 by marvinleibe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_line(char *line, t_line_struct *line_sort, int *map_started)
{
	int status = 0;
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
		printf("Error\n");
		printf("Empty line inside the map\n");
		return (1);
	}
	return (status);
}

int	read_lines_until_end(int fd, t_line_struct *line_sort, int *map_started)
{
	char	*line;
	int		keep_reading;
	int		status = 0;

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
	if(line)
		free(line);
	return (status);
}

void	emergency_exit_unfilled_textures_or_colors(t_texture *texture,
		char **map)
{
	printf("Error\n");
	printf("Unfilled textures or colors\n");
	emergency_exit(NULL, texture, map);
}

void parse_file(int fd, t_texture *texture, char ***map, t_app *app)
{
	t_line_struct line_sort;
	t_vec row_col;
	int map_started = 0;

	row_col.x = app->rows;
	row_col.y = app->cols;

	line_sort.map = map;
	line_sort.rows_cols = &row_col;
	line_sort.texture = texture;

	if (read_lines_until_end(fd, &line_sort, &map_started))
		emergency_exit(NULL, texture, *map);
	if (line_sort.rows_cols->x > 0)
		(*map)[line_sort.rows_cols->x] = NULL;
	if (line_sort.rows_cols->y > 0)
		(*map)[line_sort.rows_cols->y] = NULL;
	app->rows = line_sort.rows_cols->x;
	app->cols = line_sort.rows_cols->y;
	if (!are_textures_and_colors_filled(texture))
		emergency_exit_unfilled_textures_or_colors(texture, *map);
}

