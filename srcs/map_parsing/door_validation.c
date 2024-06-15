/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:45:23 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/15 19:47:32 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	replace_adj_door(t_app *app, char **map, t_vec xy, t_vec dydx)
{
	t_vec	n;

	n.y = xy.y + dydx.y;
	n.x = xy.x + dydx.x;
	if (n.y >= 0 && n.y < app->rows && n.x >= 0 && n.x < app->cols
		&& n.x < (int)ft_strlen(map[n.y]) && app->walked_map[n.y][n.x] == 3)
	{
		app->walked_map[xy.y][xy.x] = 1;
		app->walked_map[n.y][n.x] = 1;
		map[xy.y][xy.x] = '1';
		map[n.y][n.x] = '1';
	}
}

void	check_adj_doors(t_app *app, char **map, t_vec xy)
{
	t_vec	zero_one;
	t_vec	zero_minus_one;
	t_vec	one_zero;
	t_vec	minus_one_zero;

	zero_one.x = 0;
	zero_one.y = 1;
	zero_minus_one.x = 0;
	zero_minus_one.y = -1;
	one_zero.x = 1;
	one_zero.y = 0;
	minus_one_zero.x = -1;
	minus_one_zero.y = 0;
	if (app->walked_map[xy.y][xy.x] == 3 && app->textures->d_path)
	{
		replace_adj_door(app, map, xy, zero_one);
		replace_adj_door(app, map, xy, zero_minus_one);
		replace_adj_door(app, map, xy, one_zero);
		replace_adj_door(app, map, xy, minus_one_zero);
	}
}

void	replace_adj_doors(t_app *app, char **map)
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
