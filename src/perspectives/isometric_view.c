/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_view.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:48:15 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/16 16:48:58 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_point	isometric_view(t_fdf *fdf, t_point p)
{
	double	angle;
	t_point	res;

	angle = degree_to_rad(fdf->map.perspective_angle);
	p.specs.z *= (fdf->map.z_scale * fdf->map.zoom);
	res.x = p.y * cos(angle) - p.x * cos(angle);
	res.y = p.x * sin(angle) + p.y * sin(angle) - p.specs.z;
	res.specs = p.specs;
	return (res);
}
