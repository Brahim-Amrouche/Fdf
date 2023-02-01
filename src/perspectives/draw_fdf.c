/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:05:00 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/01 21:16:42 by bamrouch         ###   ########.fr       */
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
	int x;
	int y;

	y = 1;
	ft_printf("[%d]\n", fdf->map[1][3]);
	while (y < fdf->map[0][0])
	{
		x = 1;
		while (x < fdf->map[y][0])
		{
			if (x > 1)
				fdf_draw_block(fdf, (t_point){y, x, fdf->map[y][x]}, (t_point){y, x - 1, fdf->map[y][x - 1]});
			if (y > 1)
				fdf_draw_block(fdf, (t_point){y, x, fdf->map[y][x]}, (t_point){y - 1, x, fdf->map[y - 1][x]});
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_window, fdf->frame.img, 0, 0);
}
