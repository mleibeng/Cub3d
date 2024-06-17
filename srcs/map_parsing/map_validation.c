/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:35:36 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/17 23:07:22 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid(char c, int *player_count)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		(*player_count)++;
		if (*player_count > 1)
			return (0);
	}
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E'
		|| c == 'D');
}

int	character_validation(char **map, int rows, t_texture *textures)
{
	int	player_count;
	int	i;
	int	j;

	player_count = 0;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < (int)ft_strlen(map[i]))
		{
			if (ft_isspace(map[i][j]))
			{
				j++;
				continue ;
			}
			if (!is_valid(map[i][j], &player_count))
			{
				if (player_count > 1)
				{
					printf("Error\n");
					printf("Multiple players found in map\n");
					emergency_exit(NULL, textures, map);
				}
				else
				{
					printf("Error\n");
					printf("Invalid character inside map\n");
					emergency_exit(NULL, textures, map);
				}
			}
			if (!textures->d_path && map[i][j] == 'D')
				map[i][j] = '1';
			j++;
		}
		i++;
	}
	if (player_count == 0)
	{
		printf("Error\n");
		printf("No player found in map\n");
		emergency_exit(NULL, textures, map);
	}
	return (0);
}

void	_validate_field(char **map, t_vec *rowcol, t_app *app)
{
	f_player_start(app, map, &app->player.start_x, &app->player.start_y);
	if (app->player.start_y == -1)
	{
		printf("Error\n");
		printf("No player found\n");
		emergency_exit(app, app->textures, map);
	}
	if (!closed_map(map, rowcol, app))
	{
		printf("Error\n");
		printf("Map has leaky walls\n");
		emergency_exit(app, app->textures, map);
	}
}

char	**map_validate(t_app *app, char *file)
{
	t_vec	rowcol;
	char	**map;

	rowcol.x = 0;
	rowcol.y = 0;
	map = NULL;
	app->map = NULL;
	app->walked_map = 0;
	app->check_queue = NULL;
	app->minimap = 0;
	app->textures = read_map(file, &map, &rowcol);
	if (!app->textures)
	{
		printf("Error\n");
		printf("Error in textures\n");
		emergency_exit(app, app->textures, map);
	}
	if (character_validation(map, rowcol.x, app->textures))
	{
		printf("Error\n");
		printf("Error in character validation\n");
		emergency_exit(app, app->textures, map);
	}
	app->cols = rowcol.y;
	app->rows = rowcol.x;
	_validate_field(map, &rowcol, app);
	return (map);
}
