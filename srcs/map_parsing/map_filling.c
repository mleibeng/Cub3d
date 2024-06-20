/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_filling_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 00:55:33 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/20 02:15:24 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	allocate_map_memory(char ***map, size_t line_len, int row)
{
	if (!*map)
	{
		*map = malloc(MAX_LINE_LENGTH * sizeof(char *));
		if (!*map)
		{
			printf("Error\nMap Malloc failed\n");
			return (1);
		}
	}
	(*map)[row] = ft_calloc((line_len + 1) * sizeof(char), '0');
	if (!(*map)[row])
	{
		printf("Error\nRow Malloc failed\n");
		return (1);
	}
	(*map)[row][line_len] = '\0';
	return (0);
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

int	parse_map(char *line, char ***map, t_vec *rows_cols)
{
	size_t	line_len;
	int		status;

	status = 0;
	line_len = ft_strlen(line);
	if (ft_strlen(line) > 0)
	{
		status = allocate_map_memory(map, line_len, rows_cols->x);
		copy_line_to_map(line, *map, rows_cols->x, line_len);
		update_rows_cols(line_len, rows_cols);
	}
	return (status);
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
	app->val_map[app->player.start_y][app->player.start_x] = 2;
	while (app->start < app->end)
	{
		app->pos = app->check_queue[app->start++];
		j = -1;
		while (++j < 4)
		{
			next_x = app->pos.x + direct[j].x;
			next_y = app->pos.y + direct[j].y;
			if (!fill_bounds(next_x, next_y, app, map))
				return (printf("Error\nFill_maperror\n"), 0);
		}
	}
	if (!check_bounds(app))
		return (printf("Error\nMaperror\n"), 0);
	free_queue(app);
	return (1);
}
