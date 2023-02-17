/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:05:00 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/17 20:11:37 by bamrouch         ###   ########.fr       */
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

static void	fdf_draw_block(t_fdf *fdf, t_point axis, t_point p2)
{
	if ((axis.x > 0 && axis.x < fdf->window_info.width && axis.y > 0
			&& axis.y < fdf->window_info.height) || (p2.x > 0
			&& p2.x < fdf->window_info.width && p2.y > 0
			&& p2.y < fdf->window_info.height))
		fdf_draw_line(fdf, &axis, &p2);
}

t_point	fdf_project_point(t_fdf *fdf, t_point p)
{
	fdf_scale_points(fdf, &p);
	fdf_rotate_points(fdf, &p);
	if (fdf->map.isometric_projection)
		p = isometric_view(fdf, p);
	else
		p = parallel_view(fdf, p);
	fdf_offset_points(fdf, &p);
	if (!p.specs.color)
		p.specs.color = fdf->block_info.default_color;
	return (p);
}

t_boolean	draw_fdf(t_fdf *fdf)
{
	int		i;
	int		j;
	t_point	**projected_points;

	fdf_mlx_init_window(fdf);
	fdf_mlx_init_image(fdf);
	if (!fdf->map.projected_points)
		fdf_malloc_projected_points(fdf);
	projected_points = fdf_project_all_points(fdf);
	i = -1;
	while (++i < fdf->map.y_count)
	{
		j = -1;
		while (++j < fdf->map.x_count)
		{
			if (i > 0)
				fdf_draw_block(fdf, projected_points[i][j],
					projected_points[i - 1][j]);
			if (j > 0)
				fdf_draw_block(fdf, projected_points[i][j],
					projected_points[i][j - 1]);
		}
	}
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_window, fdf->frame.img, 0, 0);
	return (TRUE);
}
