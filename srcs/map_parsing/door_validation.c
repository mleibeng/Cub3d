/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvinleibenguth <marvinleibenguth@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:45:23 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/18 19:12:21 by marvinleibe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_door(t_app *app, char **map, t_vec xy)
{
	int	horizontal_valid;
	int	vertical_valid;

	horizontal_valid = 0;
	vertical_valid = 0;
	if (xy.y > 0 && xy.y < app->cols - 1)
	{
		if (map[xy.x][xy.y - 1] == '1' && map[xy.x][xy.y + 1] == '1')
			horizontal_valid = 1;
	}
	if (xy.x > 0 && xy.x < app->rows - 1)
	{
		if (map[xy.x - 1][xy.y] == '1' && map[xy.x + 1][xy.y] == '1')
			vertical_valid = 1;
	}
	return (horizontal_valid || vertical_valid);
}

void	check_adj_doors(t_app *app, char **map, t_vec xy)
{
	if (app->walked_map[xy.x][xy.y] == 3 && app->textures->d_path)
	{
		if (!is_valid_door(app, map, xy))
		{
			printf("Error\nInvalid door placement\n");
			emergency_exit(app, app->textures, map);
		}
	}
}

void	validate_doors(t_app *app, char **map)
{
	t_vec	xy;
	xy.x = 0;
	while (xy.x < app->rows)
	{
		xy.y = 0;
		while (xy.y < app->cols)
		{
			check_adj_doors(app, map, xy);
			xy.y++;
		}
		xy.x++;
	}
}
