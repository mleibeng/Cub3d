/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:34:29 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/15 19:48:31 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_map(char *line, char ***map, t_vec *rows_cols)
{
	if (ft_strlen(line) > 0)
	{
		if (rows_cols->x == 0)
		{
			*map = malloc(MAX_LINE_LENGTH * sizeof(char *));
			if (!*map)
			{
				free(line);
				emergency_exit(NULL, NULL, *map);
			}
		}
		(*map)[rows_cols->x] = malloc((ft_strlen(line) + 1) * sizeof(char));
		if (!(*map)[rows_cols->x])
		{
			free(line);
			emergency_exit(NULL, NULL, *map);
		}
		ft_strlcpy((*map)[rows_cols->x], line, ft_strlen(line) + 1);
		if ((int)ft_strlen(line) > rows_cols->y)
			rows_cols->y = (int)ft_strlen(line);
		(rows_cols->x)++;
	}
	free(line);
}

void	parse_file(int fd, t_texture *texture, char ***map, t_vec *rows_cols)
{
	char	*line;
	int		keep_reading;

	line = NULL;
	keep_reading = 1;
	parse_textures(fd, texture);
	parse_floor_ceiling(fd, texture);
	while (keep_reading)
	{
		line = get_cut_next_line(fd);
		if (!line)
			keep_reading = 0;
		else
			parse_map(line, map, rows_cols);
	}
	if (rows_cols->y > 0)
		(*map)[rows_cols->y] = NULL;
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
				return (perror("fill_maperror"), 0);
		}
	}
	if (!check_bounds(app))
		return (perror("maperror"), 0);
	free_queue(app);
	return (1);
}

int	**create_map(int rows, int columns)
{
	int	i;
	int	**map;

	i = 0;
	map = malloc((rows + 1) * sizeof(int *));
	if (!map)
		return (NULL);
	while (i < rows)
	{
		map[i] = ft_calloc(columns, sizeof(int));
		if (!map[i])
		{
			perror("Memory allocation failed for map row");
			while (i-- > 0)
				free(map[i]);
			free(map);
			exit(1);
		}
		i++;
	}
	map[rows] = NULL;
	return (map);
}

void	fill_minimap(char **map, int **mini_map, t_app *app)
{
	t_vec	ij;

	ij.x = 0;
	while (ij.x < app->rows)
	{
		ij.y = 0;
		while (ij.y < app->cols)
		{
			fill_minimap_bounds(map, mini_map, &ij);
			ij.y++;
		}
		ij.x++;
	}
}
