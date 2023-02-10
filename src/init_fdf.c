/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:27:30 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/10 17:34:18 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_boolean   fdf_init(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->window_info =(t_window_info) {FRAME_WIDTH, FRAME_HEIGHT};
	fdf->block_info = (t_block_info) {20, 20};
	fdf->mlx_window = mlx_new_window(fdf->mlx, fdf->window_info.width, fdf->window_info.height, "fdf");
	fdf->frame.img = mlx_new_image(fdf->mlx, fdf->window_info.width, fdf->window_info.height);
	fdf->frame.addr = mlx_get_data_addr(fdf->frame.img, &fdf->frame.bits_per_pixel, &fdf->frame.line_length,
						&fdf->frame.endian);
    return TRUE;
}