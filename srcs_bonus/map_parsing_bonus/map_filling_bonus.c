/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_filling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 00:55:33 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/18 00:58:13 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	allocate_map_memory(char ***map, size_t line_len, int row,
		t_texture *texture)
{
	if (!*map)
	{
		*map = malloc(MAX_LINE_LENGTH * sizeof(char *));
		if (!*map)
			emergency_exit(NULL, texture, *map);
	}
	(*map)[row] = malloc((line_len + 1) * sizeof(char));
	if (!(*map)[row])
		emergency_exit(NULL, texture, *map);
}

void	copy_line_to_map(char *line, char **map, int row, size_t line_len)
{
	int	i;

	i = 0;
	while (i < (int)line_len)
	{
		if (ft_isspace(line[i]))
			map[row][i] = '0';
		else
			map[row][i] = line[i];
		i++;
	}
	map[row][line_len] = '\0';
}

void	update_rows_cols(size_t line_len, t_vec *rows_cols)
{
	if ((int)line_len > rows_cols->y)
		rows_cols->y = (int)line_len;
	(rows_cols->x)++;
}

void	parse_map(char *line, char ***map, t_vec *rows_cols, t_texture *texture)
{
	size_t	line_len;

	line_len = ft_strlen(line);
	if (ft_strlen(line) > 0)
	{
		if (rows_cols->x == 0)
			allocate_map_memory(map, line_len, rows_cols->x, texture);
		allocate_map_memory(map, line_len, rows_cols->x, texture);
		copy_line_to_map(line, *map, rows_cols->x, line_len);
		update_rows_cols(line_len, rows_cols);
	}
}

int	fill_map(char **map, t_app *app, t_vec *direct)
{
	int	next_x;
	int	next_y;
	int	j;

	app->end = 0;
	app->start = 0;
	app->check_queue[app->end++] = (t_vec){app->player.start_x,
		app->player.start_y};
	app->walked_map[app->player.start_y][app->player.start_x] = 2;
	while (app->start < app->end)
	{
		app->pos = app->check_queue[app->start++];
		j = -1;
		while (++j < 4)
		{
			next_x = app->pos.x + direct[j].x;
			next_y = app->pos.y + direct[j].y;
			if (!fill_bounds(next_x, next_y, app, map))
				return (printf("Error\n"), printf("fill_maperror\n"), 0);
		}
	}
	if (!check_bounds(app))
		return (printf("Error\n"), printf("maperror\n"), 0);
	free_queue(app);
	return (1);
}
