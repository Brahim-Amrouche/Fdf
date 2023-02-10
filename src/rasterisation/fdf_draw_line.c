/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:02:28 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/10 20:35:52 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_put_line_pixels(t_fdf *fdf, t_point p1, t_point p2, t_boolean steep)
{
	double	grad;
	double	y;

	y = (double)p1.y;
	grad = 1;
	if (p2.x - p1.x)
		grad = (double)(p2.y - p1.y) / (double)(p2.x - p1.x);
	while (p1.x < p2.x)
	{
		
		if (steep)
		{
			fdf_pixel_put(fdf,(int) y, p1.x, p1.specs.color);
			fdf_pixel_put(fdf,(int) y - 1, p1.x, p1.specs.color);
		}
		else 
		{
			fdf_pixel_put(fdf, p1.x, (int)y - 1, p1.specs.color);
			fdf_pixel_put(fdf, p1.x, (int)y, p1.specs.color);
		}
		y += grad;
		p1.x++;
	}
}

void	fdf_draw_line(t_fdf *fdf, t_point *p1, t_point *p2)
{
	t_boolean steep;
	
	steep = ft_abs(p2->x - p1->x) < ft_abs( p2->y - p1->y);
	if (steep)
	{
		int_swap(&p2->x, &p2->y);
		int_swap(&p1->x, &p1->y);
	}
	if (p1->x > p2->x)
		pointer_swap((void **)&p1, (void **)&p2);
	fdf_put_line_pixels(fdf, *p1, *p2, steep);
}
