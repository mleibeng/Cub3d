/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:34:39 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/19 01:34:01 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_column_bound(t_app *app)
{
	int	j;

	j = -1;
	while (++j < app->cols)
	{
		if (app->val_map[0][j] == 2 || app->val_map[0][j] == 3)
		{
			printf("Error\nerror in check_bounds: invalid 2 found\n");
			free_queue(app);
			return (0);
		}
	}
	j = -1;
	while (++j < app->cols)
	{
		if (app->val_map[app->rows - 1][j] == 2 || app->val_map[app->rows
			- 1][j] == 3)
		{
			printf("Error\nerror in check_bounds: invalid 2 found\n");
			free_queue(app);
			return (0);
		}
	}
	return (1);
}

int	check_row_bound(t_app *app)
{
	int	i;

	i = -1;
	while (++i < app->rows)
	{
		if (app->val_map[i][0] == 2 || app->val_map[i][0] == 3)
		{
			printf("Error\nerror in check_bounds: invalid 2/3 found\n");
			free_queue(app);
			return (0);
		}
	}
	i = -1;
	while (++i < app->rows)
	{
		if (app->val_map[i][app->cols - 1] == 2
			|| app->val_map[i][app->cols - 1] == 3)
		{
			printf("Error\nerror in check_bounds: invalid 2/3 found\n");
			free_queue(app);
			return (0);
		}
	}
	return (1);
}

int	check_bounds(t_app *app)
{
	if (!check_column_bound(app))
		return (0);
	if (!check_row_bound(app))
		return (0);
	return (1);
}

int	fill_bounds(int next_x, int next_y, t_app *app, char **map)
{
	if (next_x >= 0 && next_x < app->cols && next_y >= 0 && next_y < app->rows
		&& !app->val_map[next_y][next_x])
	{
		if (map[next_y][next_x] == '0')
		{
			app->check_queue[app->end++] = (t_vec){next_x, next_y};
			app->val_map[next_y][next_x] = 2;
		}
		else if (map[next_y][next_x] == '1')
			app->val_map[next_y][next_x] = 1;
		else if (map[next_y][next_x] == 'D')
		{
			app->val_map[next_y][next_x] = 3;
			app->check_queue[app->end++] = (t_vec){next_x, next_y};
		}
		else
		{
			printf("Error\n");
			printf("error in fill_bounds, leaky walls\n");
			emergency_exit(app, app->textures, map);
		}
	}
	return (1);
}

void	fill_minimap_bounds(char **map, int **mini_map, t_vec *ij)
{
	if (ij->y < (int)ft_strlen(map[ij->x]))
	{
		if (map[ij->x][ij->y] == '1')
			mini_map[ij->x][ij->y] = 1;
		else if (map[ij->x][ij->y] == '0')
			mini_map[ij->x][ij->y] = 0;
		else if (map[ij->x][ij->y] == 'N' || map[ij->x][ij->y] == 'W'
			|| map[ij->x][ij->y] == 'S' || map[ij->x][ij->y] == 'E')
			mini_map[ij->x][ij->y] = 2;
		else if (map[ij->x][ij->y] == 'D')
			mini_map[ij->x][ij->y] = 3;
	}
	else
		mini_map[ij->x][ij->y] = 0;
}
