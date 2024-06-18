/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:34:29 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/18 00:56:55 by mleibeng         ###   ########.fr       */
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
