/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 09:34:11 by flo               #+#    #+#             */
/*   Updated: 2024/06/19 18:31:04 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	function to handle all key and mouse hooks
void	user_input_hook(t_app *app)
{
	view_change_hook(app);
	direction_change_hook(app);
}
