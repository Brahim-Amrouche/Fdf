/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:45:52 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/18 17:13:13 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_boolean	fdf_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	unsigned int	*dst;

	dst = (unsigned int *)fdf->frame.addr;
	if (x >= 0 && x < fdf->window_info.width && y >= 0
		&& y < fdf->window_info.height)
		dst[x + (y * fdf->window_info.width)] = (unsigned int)color;
	else
		return FALSE;
	return TRUE;
}
