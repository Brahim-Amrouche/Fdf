/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:02:28 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/14 18:41:11 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_draw_steep_line(t_fdf *fdf, double y, int x, int color)
{
	fdf_pixel_put(fdf, (int)y, x, fdf_color_opacity(color, 1
			- floating_point(y)));
	fdf_pixel_put(fdf, (int)y - 1, x, fdf_color_opacity(color,
			floating_point(y)));
}

static void	fdf_put_line_pixels(t_fdf *fdf, t_point p1, t_point p2,
		t_boolean steep)
{
	double	grad;
	double	y;
	int		color;
	int		x;

	x = p1.x;
	y = (double)p1.y;
	grad = 1;
	if (p2.x - p1.x)
		grad = (double)(p2.y - p1.y) / (double)(p2.x - p1.x);
	while (x < p2.x)
	{
		color = fdf_fade_color(&p1, &p2, x - p1.x);
		if (steep)
			fdf_draw_steep_line(fdf, y, x, color);
		else
		{
			fdf_pixel_put(fdf, x, (int)y - 1, fdf_color_opacity(color,
					floating_point(y)));
			fdf_pixel_put(fdf, x, (int)y, fdf_color_opacity(color, 1
					- floating_point(y)));
		}
		y += grad;
		x++;
	}
}

void	fdf_draw_line(t_fdf *fdf, t_point *p1, t_point *p2)
{
	t_boolean	steep;

	steep = ft_abs(p2->x - p1->x) < ft_abs(p2->y - p1->y);
	if (steep)
	{
		int_swap(&p2->x, &p2->y);
		int_swap(&p1->x, &p1->y);
	}
	if (p1->x > p2->x)
		pointer_swap((void **)&p1, (void **)&p2);
	fdf_put_line_pixels(fdf, *p1, *p2, steep);
}
