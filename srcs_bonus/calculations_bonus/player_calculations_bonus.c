/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_calculations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:42:49 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/15 19:47:00 by mleibeng         ###   ########.fr       */
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
		while (j < (int)ft_strlen(map[i]))
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'S'
				|| map[i][j] == 'E')
			{
				*player_x = j;
				*player_y = i;
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
