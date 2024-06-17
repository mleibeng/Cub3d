/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:34:29 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/17 23:07:16 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'D' && line[i] != 'S'
			&& line[i] != 'W' && line[i] != 'N' && line[i] != 'E'
			&& !ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	parse_map(char *line, char ***map, t_vec *rows_cols, t_texture *texture)
{
	size_t	line_len;
	int		i;

	if (ft_strlen(line) > 0 && is_map_line(line))
	{
		if (rows_cols->x == 0)
		{
			*map = malloc(MAX_LINE_LENGTH * sizeof(char *));
			if (!*map)
			{
				free(line);
				emergency_exit(NULL, texture, *map);
			}
		}
		line_len = ft_strlen(line);
		(*map)[rows_cols->x] = malloc((line_len + 1) * sizeof(char));
		if (!(*map)[rows_cols->x])
		{
			free(line);
			emergency_exit(NULL, texture, *map);
		}
		i = 0;
		while (i < (int)line_len)
		{
			if (ft_isspace(line[i]))
				(*map)[rows_cols->x][i] = '0';
			else
				(*map)[rows_cols->x][i] = line[i];
			i++;
		}
		(*map)[rows_cols->x][line_len] = '\0';
		if ((int)line_len > rows_cols->y)
			rows_cols->y = (int)line_len;
		(rows_cols->x)++;
	}
}

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

void	parse_file(int fd, t_texture *texture, char ***map, t_vec *rows_cols)
{
	char	*line;
	int		keep_reading;
	int		map_started;
	int		map_ended;

	keep_reading = 1;
	map_started = 0;
	map_ended = 0;
	while (keep_reading)
	{
		line = get_cut_next_line(fd);
		if (!line)
			keep_reading = 0;
		else
		{
			if (ft_strlen(line) > 0)
			{
				if (map_started)
				{
					if (is_map_line(line))
						parse_map(line, map, rows_cols, texture);
					else
						map_ended = 1;
				}
				else if ((!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ",
							2)) && !map_started)
					parse_floor_ceiling(line, texture, *map);
				else if ((is_texture_line(line)) && !map_started)
					parse_textures(line, texture, *map);
				else if (is_map_line(line))
				{
					map_started = 1;
					parse_map(line, map, rows_cols, texture);
				}
			}
			free(line);
			if (map_ended)
			{
				if (!are_textures_filled(texture)
					|| !are_colors_filled(texture))
				{
					printf("Error\n");
					printf("Unfilled textures or colors after map\n");
					emergency_exit(NULL, texture, *map);
				}
				keep_reading = 0;
			}
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

int	**create_map(int rows, int columns, t_app *app)
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
			printf("Error\n");
			printf("Memory allocation failed for map row\n");
			while (i-- > 0)
				free(map[i]);
			free(map);
			emergency_exit(app, app->textures, NULL);
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
