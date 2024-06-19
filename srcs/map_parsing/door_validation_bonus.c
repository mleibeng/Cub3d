/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_validation_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:45:23 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/19 20:38:35 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n");
		printf("Error opening texture file\n");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	is_valid_door(t_app *app, char **map, t_vec xy)
{
	int	horizontal_valid;
	int	vertical_valid;

	horizontal_valid = 0;
	vertical_valid = 0;
	if (xy.x > 0 && xy.x < app->cols - 1)
	{
		if (map[xy.y][xy.x - 1] == '1' && map[xy.y][xy.x + 1] == '1')
			horizontal_valid = 1;
	}
	if (xy.y > 0 && xy.y < app->rows - 1)
	{
		if (map[xy.y - 1][xy.x] == '1' && map[xy.y + 1][xy.x] == '1')
			vertical_valid = 1;
	}
	return (horizontal_valid || vertical_valid);
}

void	check_adj_doors(t_app *app, char **map, t_vec xy)
{
	if (app->val_map[xy.y][xy.x] == 3 && app->textures->d_path)
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

	xy.y = 0;
	while (xy.y < app->rows)
	{
		xy.x = 0;
		while (xy.x < app->cols)
		{
			check_adj_doors(app, map, xy);
			xy.x++;
		}
		xy.y++;
	}
}
