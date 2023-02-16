/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_view.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:09:21 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/16 16:49:04 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	parallel_view(t_fdf *fdf, t_point p)
{
	double	angle;
	t_point	res;

	angle = degree_to_rad(fdf->map.perspective_angle);
	p.specs.z *= (fdf->map.z_scale * fdf->map.zoom);
	res.x = p.y + cos(angle) * p.x;
	res.y = sin(angle) * p.x - p.specs.z;
	res.specs = p.specs;
	return (res);
}
