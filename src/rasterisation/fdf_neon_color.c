/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_neon_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:55:52 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/17 20:03:53 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int	fdf_neon_color_move(t_point *p, int y_count, int neon_step)
{
	t_rgb	color1_rgb;
	t_rgb	color2_rgb;
	int		pos;
	double	ratio;

	pos = ((p->y + neon_step) % y_count);
	fdf_split_rgb(N_COLOR1, &color1_rgb);
	fdf_split_rgb(N_COLOR2, &color2_rgb);
	ratio = (double)(color2_rgb.red - color1_rgb.red) / y_count;
	color1_rgb.red += (double)ratio * pos;
	ratio = (double)(color2_rgb.green - color1_rgb.green) / y_count;
	color1_rgb.green += (double)ratio * pos;
	ratio = (double)(color2_rgb.blue - color1_rgb.blue) / y_count;
	color1_rgb.blue += (double)ratio * pos;
	return ((color1_rgb.red << 16) + (color1_rgb.green << 8) + color1_rgb.blue);
}
