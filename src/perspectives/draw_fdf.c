/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:05:00 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/16 18:44:18 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_scale_points(t_fdf *fdf, t_point *p)
{
	p->x = (p->x - fdf->map.x_count / 2) * (fdf->block_info.width
			* fdf->map.zoom);
	p->y = (p->y - fdf->map.y_count / 2) * (fdf->block_info.height
			* fdf->map.zoom);
	if (ft_abs(p->specs.z) < fdf->map.heighest_point * 0.85)
		p->specs.z *= 0.95;
}

static void	fdf_offset_points(t_fdf *fdf, t_point *p)
{
	p->x += fdf->window_info.width / 2 + (fdf->window_info.width
			* fdf->map.horizontal_offset);
	p->y += fdf->window_info.height / 2 + (fdf->window_info.height
			* fdf->map.vertical_offset);
}

static void	fdf_project_points(t_fdf *fdf, t_point *p1, t_point *p2)
{
	fdf_scale_points(fdf, p1);
	fdf_scale_points(fdf, p2);
	fdf_rotate_points(fdf, p1);
	fdf_rotate_points(fdf, p2);
	if (fdf->map.isometric_projection)
	{
		*p1 = isometric_view(fdf, *p1);
		*p2 = isometric_view(fdf, *p2);
	}
	else
	{
		*p1 = parallel_view(fdf, *p1);
		*p2 = parallel_view(fdf, *p2);
	}
	fdf_offset_points(fdf, p1);
	fdf_offset_points(fdf, p2);
}

static void	fdf_draw_block(t_fdf *fdf, t_point p1, t_point p2)
{
	fdf_project_points(fdf, &p1, &p2);
	if (!p1.specs.color)
		p1.specs.color = fdf->block_info.default_color;
	if (!p2.specs.color)
		p2.specs.color = fdf->block_info.default_color;
	if ((p1.x > 0 && p1.x < fdf->window_info.width && p1.y > 0
			&& p1.y < fdf->window_info.height) || (p2.x > 0
			&& p2.x < fdf->window_info.width && p2.y > 0
			&& p2.y < fdf->window_info.height))
		fdf_draw_line(fdf, &p1, &p2);
}

t_boolean	draw_fdf(t_fdf *fdf)
{
	int	i;
	int	j;

	fdf_mlx_init_window(fdf);
	fdf_mlx_init_image(fdf);
	i = 0;
	while (i < fdf->map.y_count)
	{
		j = 0;
		while (j < fdf->map.x_count)
		{
			if (i > 0)
				fdf_draw_block(fdf, (t_point){i, j, fdf->map.specs[i][j]},
						(t_point){i - 1, j, fdf->map.specs[i - 1][j]});
			if (j > 0)
				fdf_draw_block(fdf, (t_point){i, j, fdf->map.specs[i][j]},
						(t_point){i, j - 1, fdf->map.specs[i][j - 1]});
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_window, fdf->frame.img, 0, 0);
	return (TRUE);
}
