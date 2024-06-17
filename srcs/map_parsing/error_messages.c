/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 00:53:28 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/18 00:53:36 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error_and_exit(const char *message, t_texture *textures,
		char **map)
{
	printf("Error\n");
	printf("%s\n", message);
	emergency_exit(NULL, textures, map);
}
