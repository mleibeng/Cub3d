/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 22:37:06 by flo               #+#    #+#             */
/*   Updated: 2024/06/05 23:43:36 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

typedef struct s_coord{
	int xw;
	int	yw;
}	t_coord;

//	function to check if there is an error with the pixel position
int	check_error_pixel(t_coord *pt_a, t_coord *pt_b, int *x0, int *y0)
{
	static int	err = INT_MAX;

	if (err == INT_MAX)
		err = abs(pt_b->xw - pt_a->xw) - abs(pt_b->yw - pt_a->yw);
	if (*x0 == (pt_b->xw) && *y0 == pt_b->yw)
		return (err = INT_MAX, err);
	if ((2 * err) > -abs(pt_b->yw - pt_a->yw))
	{
		err -= abs(pt_b->yw - pt_a->yw);
		if (pt_a->xw < pt_b->xw)
			*x0 += 1;
		else
			*x0 -= 1;
	}
	else if ((2 * err) < abs(pt_b->xw - pt_a->xw))
	{
		err += abs(pt_b->xw - pt_a->xw);
		if (pt_a->yw < pt_b->yw)
			*y0 += 1;
		else
			*y0 -= 1;
	}
	return (err);
}

//	function to check, if a point is on a line between two points:
//	((Px - Ax)(By - Ay) - (Py -Ay)(Bx - Ax)) == 0 (A = cur, B = next)
//	then a check if point is between the points A and B
//	laslty calculate the z axis of P with , and dislpay it
void	draw_line(t_app *app, int x1, int y1, int x2, int y2, int32_t color)
{
	int		x0;
	int		y0;
	int		err;
	t_coord	point_a;
	t_coord	point_b;

	point_a.xw = x1;
	point_a.yw = y1;
	point_b.xw = x2;
	point_b.yw = y2;
	if (app == NULL)
		return ;
	x0 = x1;
	y0 = y1;
	while (1)
	{
		if (x0 > 0 && x0 < app->window_width && y0 > 0 && y0 < app->window_height)
		{
			mlx_put_pixel(app->compass, x0, y0, color);
		}
		err = check_error_pixel(&point_a, &point_b, &x0, &y0);
		if (err == INT_MAX)
			break ;
	}
}

// Function to clear the compass background
void clear_compass(mlx_image_t *img, int32_t background_color)
{
	int	y;
	int	x;
	int dx;
	int dy;

	y = 0;
	while (y < COMPASS_SIZE)
	{
		x = 0;
		while (x < COMPASS_SIZE)
		{
			dx = x - CENTER;
			dy = y - CENTER;
			if (dx * dx + dy * dy <= CENTER * CENTER)
				mlx_put_pixel(img, x, y, background_color);
			x++;
		}
		y++;
	}
}

// Function to draw the compass
void draw_compass(t_app *app, float player_angle)
{
    int32_t color;
	int		x;
	int		y;
	int		needle_length;
	int		angle;
	int32_t	background_color;

	color = 0xFFFFFFCC;
	angle = 0;
	background_color = 0x000000FF;
    clear_compass(app->compass, background_color);
	int thickness = 0;
	while (thickness < 3)
	{
			angle = 0;
			while ( angle < 360)
			{
				x = CENTER + (CENTER - 1 - thickness) * cos(angle * M_PI / 180);
				y = CENTER + (CENTER - 1 - thickness) * sin(angle * M_PI / 180);
				mlx_put_pixel(app->compass, x, y, color);
				angle += 5;
			}
			thickness++;
    }
    draw_line(app, CENTER, CENTER, CENTER, 0, color);
    draw_line(app, CENTER, CENTER, COMPASS_SIZE, CENTER, color);
    draw_line(app, CENTER, CENTER, CENTER, COMPASS_SIZE, color);
    draw_line(app, CENTER, CENTER, 0, CENTER, color);
    needle_length = CENTER - 5;
    app->needle_x = CENTER + needle_length * cos(player_angle);
    app->needle_y = CENTER + needle_length * sin(player_angle);
    draw_line(app, CENTER, CENTER, app->needle_x, app->needle_y, 0xFF0000CC);
}

// Function to create and display the compass
void display_compass(t_app *app, float player_angle)
{
	draw_compass(app, player_angle);
}

