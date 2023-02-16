/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:45:30 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/16 20:49:13 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_rotate_x(t_fdf *fdf, t_point *p)
{
	double	degree;
	int		temp_y;

	degree = degree_to_rad(fdf->map.rot_x);
	temp_y = p->y;
	p->x = p->x;
	p->y = cos(degree) * p->y - sin(degree) * p->specs.z;
	p->specs.z = temp_y * sin(degree) + p->specs.z * cos(degree);
}

static void	fdf_rotate_y(t_fdf *fdf, t_point *p)
{
	double	degree;
	int		temp_x;

	degree = degree_to_rad(fdf->map.rot_y);
	temp_x = p->x;
	p->x = cos(degree) * p->x + sin(degree) * p->specs.z;
	p->y = p->y;
	p->specs.z = cos(degree) * p->specs.z - sin(degree) * temp_x;
}

static void	fdf_rotate_z(t_fdf *fdf, t_point *p)
{
	double	degree;
	int		temp_x;

	degree = degree_to_rad(fdf->map.rot_z);
	temp_x = p->x;
	p->x = cos(degree) * p->x - sin(degree) * p->y;
	p->y = sin(degree) * temp_x + cos(degree) * p->y;
	p->specs.z = p->specs.z;
}

void	fdf_rotate_points(t_fdf *fdf, t_point *p)
{
	fdf_rotate_x(fdf, p);
	fdf_rotate_y(fdf, p);
	fdf_rotate_z(fdf, p);
}
