/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_and_line_checks.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 02:20:36 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/19 18:07:19 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d_bonus.h"

int	is_texture_line(char *line)
{
	return (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3));
}

int	are_textures_filled(t_texture *texture)
{
	return (texture->n_path != NULL && texture->s_path != NULL
		&& texture->w_path != NULL && texture->e_path != NULL);
}

int	are_colors_filled(t_texture *texture)
{
	return (texture->floor[0] != -1 && texture->skybox[0] != -1);
}

int	are_textures_and_colors_filled(t_texture *texture)
{
	return (are_textures_filled(texture) && are_colors_filled(texture));
}
