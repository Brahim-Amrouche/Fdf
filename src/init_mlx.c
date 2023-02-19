/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:27:30 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/19 15:39:28 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_mlx_init_window(t_fdf *fdf)
{
	if (!fdf->mlx_window)
	{
		fdf->mlx_window = mlx_new_window(fdf->mlx,
				fdf->window_info.width, fdf->window_info.height, "fdf");
		if (!fdf->mlx_window)
			exit_fdf(fdf, EAGAIN, "\tmlx new window didnt work", TRUE);
		fdf_hooks(fdf);
	}
	else
		mlx_clear_window(fdf->mlx, fdf->mlx_window);
}

void	fdf_mlx_init_image(t_fdf *fdf)
{
	if (!fdf->frame.img)
	{
		fdf->frame.img = mlx_new_image(fdf->mlx, fdf->window_info.width,
				fdf->window_info.height);
		if (!fdf->frame.img)
			exit_fdf(fdf, EAGAIN, "\tmlx new image didnt work", TRUE);
		fdf->frame.addr = mlx_get_data_addr(fdf->frame.img,
				&fdf->frame.bits_per_pixel, &fdf->frame.line_length,
				&fdf->frame.endian);
		if (!fdf->frame.addr)
			exit_fdf(fdf, EAGAIN, "\tmlx get data addr didnt work", TRUE);
	}
	else
	{
		mlx_destroy_image(fdf->mlx, fdf->frame.img);
		fdf->frame.img = NULL;
		fdf->frame.addr = NULL;
		fdf_mlx_init_image(fdf);
	}
}

void	fdf_mlx_init(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		exit_fdf(fdf, EAGAIN, "\tmlx init didnt work", TRUE);
	fdf->window_info = (t_window_info){FRAME_WIDTH, FRAME_HEIGHT};
	fdf->map.zoom = 1;
	fdf->map.perspective_angle = 30;
	fdf->map.isometric_projection = TRUE;
}
