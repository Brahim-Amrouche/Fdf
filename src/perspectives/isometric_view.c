/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_view.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:48:15 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/12 20:56:33 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_point	isometric_view(t_fdf *fdf, t_point p)
{
	double angle;
	double angle2;
	t_point res;

	angle2 = 0;
	angle = 30;
	p.x = (p.x - fdf->map.x_count / 2) * ( fdf->block_info.width * fdf->map.zoom);
	p.y = (p.y - fdf->map.y_count / 2) * (fdf->block_info.height * fdf->map.zoom);
	if(ft_abs(p.specs.z) < fdf->map.heighest_point * 0.85)
		p.specs.z *= 0.95;
	p.specs.z *= (fdf->map.z_scale * fdf->map.zoom);
	res.x = p.x * cos(degree_to_rad(90 + 2 * angle)) + p.y
		* cos(degree_to_rad(angle)) + p.specs.z * sin(degree_to_rad(-30 + angle));
	res.y = p.x * sin(degree_to_rad(90 + 2 * angle)) + p.y
		* sin(degree_to_rad(angle)) - p.specs.z * cos(degree_to_rad(-30 + angle));
	res.x += fdf->window_info.width / 2 + (fdf->window_info.width * fdf->map.horizontal_offset);
	res.y += fdf->window_info.height / 2 + (fdf->window_info.height * fdf->map.vertical_offset);
	res.specs = p.specs;
	return (res);
}