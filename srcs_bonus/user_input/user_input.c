/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 09:34:11 by flo               #+#    #+#             */
/*   Updated: 2024/06/19 18:08:24 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d_bonus.h"

//	function to handle all key and mouse hooks
void	user_input_hook(t_app *app)
{
	view_change_hook(app);
	mouse_shift(app);
	direction_change_hook(app);
}
