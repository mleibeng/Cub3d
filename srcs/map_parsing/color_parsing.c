/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:34:14 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/15 19:47:08 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	color_validation(char *end, char *line, int val)
{
	if (end != line && *end != ',')
	{
		perror("invalid RGB values\n");
		exit(1);
	}
	if (val < 0 || val > 255)
	{
		perror("RGB values must be between 0 and 255");
		exit(1);
	}
}

void	save_rgb(char *line, int *color)
{
	char	*end;
	int		r;
	int		g;
	int		b;

	r = ft_strtoi(line, &end);
	color_validation(end, line, r);
	line = end + 1;
	g = ft_strtoi(line, &end);
	color_validation(end, line, g);
	line = end + 1;
	b = ft_strtoi(line, &end);
	if (b < 0 || b > 255)
	{
		perror("RGB values must be between 0 and 255");
		exit(1);
	}
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = 0;
}

void	parse_floor_ceiling(int fd, t_texture *texture)
{
	char	*line;
	int		keep_reading;

	line = NULL;
	keep_reading = 1;
	while (keep_reading && (!texture->floor[0] || !texture->skybox[0]))
	{
		line = get_cut_next_line(fd);
		if (!line)
			keep_reading = 0;
		else
		{
			if (ft_strlen(line) > 0)
			{
				if (!ft_strncmp(line, "F ", 2))
					save_rgb(line + 2, texture->floor);
				else if (!ft_strncmp(line, "C ", 2))
					save_rgb(line + 2, texture->skybox);
			}
			free(line);
		}
	}
	if (!line)
		emergency_exit(NULL, texture, NULL);
}
