/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_view.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:09:21 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/14 19:21:53 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	parallel_view(t_fdf *fdf, t_point p)
{
	double	angle;
	t_point	res;

	angle = degree_to_rad(fdf->map.rot_angle);
	p.x = (p.x - fdf->map.x_count / 2) * (fdf->block_info.width
			* fdf->map.zoom);
	p.y = (p.y - fdf->map.y_count / 2) * (fdf->block_info.height
			* fdf->map.zoom);
	if (ft_abs(p.specs.z) < fdf->map.heighest_point * 0.85)
		p.specs.z *= 0.95;
	p.specs.z *= (fdf->map.z_scale * fdf->map.zoom);
	res.x = p.y + cos(angle) * p.x;
	res.y = sin(angle) * p.x - p.specs.z;
	res.x += fdf->window_info.width / 2 + (fdf->window_info.width
			* fdf->map.horizontal_offset);
	res.y += fdf->window_info.height / 2 + (fdf->window_info.height
			* fdf->map.vertical_offset);
	res.specs = p.specs;
	return (res);
}