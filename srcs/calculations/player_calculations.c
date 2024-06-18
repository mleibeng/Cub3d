/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_calculations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvinleibenguth <marvinleibenguth@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:42:49 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/18 18:59:24 by marvinleibe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	check_start_angle(char direction)
{
	float	start_angle;

	start_angle = 0.0;
	if (direction == 'N')
		start_angle = M_PI + M_PI_2;
	else if (direction == 'E')
		start_angle = 0.0;
	else if (direction == 'S')
		start_angle = M_PI - M_PI_2;
	else if (direction == 'W')
		start_angle = M_PI;
	return (start_angle);
}

void	f_player_start(t_app *app, char **map, int *player_x, int *player_y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'S'
				|| map[i][j] == 'E')
			{
				*player_x = i;
				*player_y = j;
				app->player.angle = check_start_angle(map[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
	*player_x = -1;
	*player_y = -1;
}
