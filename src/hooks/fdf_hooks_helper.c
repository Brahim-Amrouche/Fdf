/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:10:08 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/16 18:43:05 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	rotate_hook(int x, int y, t_fdf *fdf)
{
	int	x_start;
	int	y_start;

	if (fdf->map.activate_rot)
	{
		x_start = fdf->map.rot_start[0];
		y_start = fdf->map.rot_start[1];
		fdf->map.rot_z += (double)((double)(x - x_start)
				/ (fdf->window_info.width - x_start)) * 2;
		fdf->map.rot_y += (double)((double)(y - y_start)
				/ (fdf->window_info.height - y_start)) * 2;
	}
	return (0);
}

int	mouse_release_hook(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == LEFT_CLIC)
		fdf->map.activate_rot = FALSE;
	return (0);
}
