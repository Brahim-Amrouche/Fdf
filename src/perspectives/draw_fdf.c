/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:05:00 by bamrouch          #+#    #+#             */
/*   Updated: 2023/01/31 19:03:00 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_draw_block(t_fdf *fdf, t_point p1, t_point p2)
{
	p1 = isometric_view(fdf, p1);
	p2 = isometric_view(fdf, p2);
	fdf_draw_line(fdf, &p1, &p2);
}

void	draw_fdf(t_fdf *fdf)
{
	unsigned int x;
	unsigned int y;
	unsigned int z;

	x = 0;
	z = 0;
	while (x <= 10)
	{
		y = 0;
		while (y <= 10)
		{
			if (x > 0)
				fdf_draw_block(fdf, (t_point){x, y, z}, (t_point){x - 1, y, z});
			if (y > 0)
				fdf_draw_block(fdf, (t_point){x, y, z}, (t_point){x, y - 1, z});
			z = (z + 1) % 3;
			y++;
		}
		x++;
	}
	fdf_draw_block(fdf,(t_point){0, 0, 0}, (t_point){0, 1, 0});
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_window, fdf->frame.img, 0, 0);
}
