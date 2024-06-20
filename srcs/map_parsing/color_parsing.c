/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:34:14 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/19 20:38:36 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color_validation(char *end, int val)
{
	while (end && *end && ft_isspace(*end))
		end++;
	if (end && *end && *end != ',' && *end != '\0')
	{
		printf("Error\n");
		printf("Invalid RGB values\n");
		return (1);
	}
	if (val < 0 || val > 255)
	{
		printf("Error\n");
		printf("RGB values must be between 0 and 255");
		return (1);
	}
	return (0);
}

int	check_valid_colors(char *line)
{
	char	*p;

	p = line;
	while (*p)
	{
		if (!ft_isdigit(*p) && *p != ',' && !ft_isspace(*p))
		{
			printf("Error\n");
			printf("Invalid RGB values: non-numeric characters found\n");
			return (1);
		}
		p++;
	}
	return (0);
}

int	check_valid_end(char *end)
{
	while (*end && ft_isspace(*end))
		end++;
	if (*end != '\0')
	{
		printf("Error\n");
		printf("Invalid RGB values: extra characters after blue value\n");
		return (1);
	}
	return (0);
}

int	save_rgb(char *line, int *color)
{
	char	*end;

	if (check_valid_colors(line))
		return (1);
	while (*line && ft_isspace(*line))
		line++;
	color[0] = ft_strtoi(line, &end);
	if (color_validation(end, color[0]))
		return (1);
	line = end;
	while (*line && (ft_isspace(*line) || *line == ','))
		line++;
	color[1] = ft_strtoi(line, &end);
	if (color_validation(end, color[1]))
		return (1);
	line = end;
	while (*line && (ft_isspace(*line) || *line == ','))
		line++;
	color[2] = ft_strtoi(line, &end);
	if (color_validation(end, color[2]))
		return (1);
	if (check_valid_end(end))
		return (1);
	color[3] = 0;
	return (0);
}

int	parse_floor_ceiling(char *line, t_texture *texture)
{
	int	exit_prog;

	exit_prog = 0;
	if (texture->floor[0] == -1 || texture->skybox[0] == -1)
	{
		if (!ft_strncmp(line, "F ", 2))
			exit_prog = save_rgb(line + 2, texture->floor);
		else if (!ft_strncmp(line, "C ", 2))
			exit_prog = save_rgb(line + 2, texture->skybox);
	}
	if (!line)
	{
		printf("Error\n");
		printf("invalid filestop at color readin");
		exit_prog = 1;
	}
	return (exit_prog);
}
