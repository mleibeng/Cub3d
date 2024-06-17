/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:34:14 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/17 20:52:20 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	color_validation(char *end, char *line, int val)
{
	if (end != line && *end != ',')
	{
		if(line)
		{
			perror("Invalid RGB values\n");
			exit(1);
		}
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
	char 	*start = line;
	char	*p;

	p = start;
	while (*p)
	{
		if (!ft_isdigit(*p) && *p != ',' && !ft_isspace(*p))
		{
			perror("Invalid RGB values: non-numeric characters found\n");
			exit(1);
		}
		p++;
	}
	r = ft_strtoi(line, &end);
	color_validation(end, line, r);
	line = end + 1;
	g = ft_strtoi(line, &end);
	color_validation(end, line, g);
	line = end + 1;
	b = ft_strtoi(line, &end);
	color_validation(end, NULL, b);
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = 0;
}

void	parse_floor_ceiling(char *line, t_texture *texture)
{
	if (texture->floor[0] == -1 || texture->skybox[0] == -1)
	{
		if (!ft_strncmp(line, "F ", 2))
			save_rgb(line + 2, texture->floor);
		else if (!ft_strncmp(line, "C ", 2))
			save_rgb(line + 2, texture->skybox);
		if (!line)
			emergency_exit(NULL, texture, NULL);
	}
}
