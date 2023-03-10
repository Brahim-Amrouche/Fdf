/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:02:28 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/17 15:5 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_boolean	fdf_draw_steep_line(t_fdf *fdf, double y, int x, int color)
{
	t_boolean	pixel_is_put;

	pixel_is_put = fdf_pixel_put(fdf, (int)y, x,
			fdf_color_opacity(color, 1 - floating_point(y)));
	pixel_is_put = fdf_pixel_put(fdf, (int)y - 1, x,
			fdf_color_opacity(color, floating_point(y)));
	return (pixel_is_put);
}

static t_boolean	fdf_draw_straight_line(t_fdf *fdf, int x, double y,
		int color)
{
	t_boolean	pixel_is_put;

	pixel_is_put = fdf_pixel_put(fdf, x, (int)y - 1, fdf_color_opacity(color,
				floating_point(y)));
	pixel_is_put = fdf_pixel_put(fdf, x, (int)y, fdf_color_opacity(color, 1
				- floating_point(y)));
	return (pixel_is_put);
}

static void	fdf_put_line_pixels(t_fdf *fdf, t_point p1, t_point p2,
		t_boolean steep)
{
	double		grad;
	double		y;
	int			color;
	int			x;
	t_boolean	pixel_is_put;

	x = p1.x;
	y = (double)p1.y;
	grad = 1;
	if (p2.x - p1.x)
		grad = (double)(p2.y - p1.y) / (double)(p2.x - p1.x);
	while (x < p2.x)
	{
		color = fdf_fade_color(&p1, &p2, x - p1.x);
		if (steep)
			pixel_is_put = fdf_draw_steep_line(fdf, y, x, color);
		else
			pixel_is_put = fdf_draw_straight_line(fdf, x, y, color);
		if (!pixel_is_put)
			break ;
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
