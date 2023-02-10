/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_view.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:48:15 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/10 20:19:42 by bamrouch         ###   ########.fr       */
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
	p.x *= fdf->block_info.width;
	p.y *= fdf->block_info.height;
	p.specs.z *= 2;
	res.x = p.x * cos(degree_to_rad(90 + 2 * angle)) + p.y
		* cos(degree_to_rad(angle)) + p.specs.z * sin(degree_to_rad(-30 + angle));
	res.y = p.x * sin(degree_to_rad(90 + 2 * angle)) + p.y
		* sin(degree_to_rad(angle)) - p.specs.z * cos(degree_to_rad(-30 + angle));
	p.x = res.x * cos(degree_to_rad(angle2)) + res.y
		* sin(degree_to_rad(angle2));
	res.y = -res.x * sin(degree_to_rad(angle2)) + res.y
		* cos(degree_to_rad(angle2));
	res.x = p.x;
	res.x += fdf->window_info.width / 2;
	res.y += fdf->window_info.height / 2;
	res.specs = p.specs;
	return (res);
}