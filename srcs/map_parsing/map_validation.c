/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:35:36 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/15 19:47:23 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E'
		|| c == 'D');
}

int	character_validation(char **map, int rows, t_texture *textures)
{
	int	i;
	int	j;

	i = -1;
	while (++i < rows)
	{
		j = -1;
		while (++j < (int)ft_strlen(map[i]) - 1)
		{
			if (ft_isspace(map[i][j]))
			{
				j++;
				continue ;
			}
			if (!is_valid(map[i][j]))
			{
				free_map((void **)map);
				free_textures(textures);
				return (perror("Invalid character inside map"), 1);
			}
			if (!textures->d_path && map[i][j] == 'D')
				map[i][j] = '1';
		}
	}
	return (0);
}

void	_validate_field(char **map, t_vec *rowcol, t_app *app)
{
	f_player_start(app, map, &app->player.start_x, &app->player.start_y);
	if (app->player.start_y == -1)
	{
		perror("No player found");
		free_map((void **)map);
		free_textures(app->textures);
		exit(EXIT_FAILURE);
	}
	if (!closed_map(map, rowcol, app))
	{
		perror("Map has leaky walls");
		free_map((void **)map);
		free_textures(app->textures);
		exit(EXIT_FAILURE);
	}
}

char	**map_validate(t_app *app, char *file)
{
	t_vec	rowcol;
	char	**map;

	rowcol.x = 0;
	rowcol.y = 0;
	map = NULL;
	app->textures = read_map(file, &map, &rowcol);
	if (!app->textures)
	{
		perror("Error in textures");
		exit(EXIT_FAILURE);
	}
	if (character_validation(map, rowcol.x, app->textures))
	{
		perror("Error in character validation");
		exit(EXIT_FAILURE);
	}
	app->cols = rowcol.y;
	app->rows = rowcol.x;
	_validate_field(map, &rowcol, app);
	return (map);
}
