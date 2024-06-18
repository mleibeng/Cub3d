/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:35:36 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/19 00:17:40 by mleibeng         ###   ########.fr       */
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

void	validate_character(char c, int *player_count, t_texture *textures,
		char **map)
{
	if (!is_valid(c, player_count))
	{
		if (*player_count > 1)
			print_error_and_exit("Multiple players found in map", textures,
				map);
		else
			print_error_and_exit("Invalid character inside map", textures, map);
	}
	if (!textures->d_path && c == 'D')
		c = '1';
}

int	character_validation(char **map, t_texture *textures)
{
	int	player_count;
	int	i;
	int	j;

	player_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (!ft_isspace(map[i][j]))
				validate_character(map[i][j], &player_count, textures, map);
			j++;
		}
		i++;
	}
	if (player_count == 0)
		print_error_and_exit("No player found in map", textures, map);
	return (0);
}

void	_validate_field(char **map, t_app *app)
{
	f_player_start(app, map, &app->player.start_x, &app->player.start_y);
	if (app->player.start_y == -1)
	{
		printf("Error\n");
		printf("No player found\n");
		emergency_exit(app, app->textures, map);
	}
	if (!closed_map(map, app))
	{
		printf("Error\n");
		printf("Map has leaky walls\n");
		emergency_exit(app, app->textures, map);
	}
}

char	**map_validate(t_app *app, char *file)
{
	char	**map;
	t_vec	rowcol;

	rowcol.x = 0;
	rowcol.y = 0;
	map = NULL;
	app->textures = read_map(file, &map, &rowcol);
	if (!app->textures)
	{
		printf("Error\n");
		printf("Error in textures\n");
		emergency_exit(app, app->textures, map);
	}
	if (character_validation(map, app->textures))
	{
		printf("Error\n");
		printf("Error in character validation\n");
		emergency_exit(app, app->textures, map);
	}
	app->cols = rowcol.y;
	app->rows = rowcol.x;
	_validate_field(map, app);
	return (map);
}
