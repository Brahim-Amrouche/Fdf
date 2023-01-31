/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:02:28 by bamrouch          #+#    #+#             */
/*   Updated: 2023/01/31 13:52:35 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_put_line_pixels(t_fdf *fdf, t_point p1, t_point p2)
{
	double	grad;
	double	y;

	y = (double)p1.y;
	grad = 1;
	if (p2.x - p1.x)
		grad = (double)(p2.y - p1.y) / (double)(p2.x - p1.x);
	while (p1.x < p2.x)
	{
		fdf_pixel_put(fdf, p1.x, (int)y - 1, fdf->block_info.color);
		fdf_pixel_put(fdf, p1.x, (int)y, fdf->block_info.color);
		y += grad;
		p1.x++;
	}
}

void	fdf_draw_line(t_fdf *fdf, t_point *p1, t_point *p2)
{
	if (p1->x > p2->x)
		pointer_swap((void **)&p1, (void **)&p2);
	fdf_put_line_pixels(fdf, *p1, *p2);
}
