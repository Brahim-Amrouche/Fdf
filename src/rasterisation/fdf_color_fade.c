/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color_fade.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:57:53 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/16 19:27:31 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fdf_rgb_fade(double color_shade_diff, double total_distance,
	int distance_passed)
{
	return ((color_shade_diff / total_distance) * distance_passed);
}

int	fdf_rgb_picker(unsigned int color, int shade, int shift)
{
	return ((color & shade) >> shift);
}

int	fdf_color_opacity(unsigned int color, double grad)
{
	unsigned int	opacity;

	opacity = (0xFF * grad);
	color = (color | (opacity << 24));
	return (color);
}

void	fdf_split_rgb(unsigned int color, t_rgb *p_rgb)
{
	p_rgb->red = fdf_rgb_picker(color, RED_SHADE, 16);
	p_rgb->green = fdf_rgb_picker(color, GREEN_SHADE, 8);
	p_rgb->blue = fdf_rgb_picker(color, BLUE_SHADE, 0);
}

int	fdf_fade_color(t_point *p1, t_point *p2, int distance_passed)
{
	int		total_distance;
	t_rgb	p1_rgb;
	t_rgb	p2_rgb;

	total_distance = p2->x - p1->x;
	fdf_split_rgb(p1->specs.color, &p1_rgb);
	fdf_split_rgb(p2->specs.color, &p2_rgb);
	p1_rgb.red += fdf_rgb_fade(p2_rgb.red - p1_rgb.red, total_distance,
			distance_passed);
	p1_rgb.green += fdf_rgb_fade(p2_rgb.green - p1_rgb.green, total_distance,
			distance_passed);
	p1_rgb.blue += fdf_rgb_fade(p2_rgb.blue - p1_rgb.blue, total_distance,
			distance_passed);
	return ((p1_rgb.red << 16) + (p1_rgb.green << 8) + p1_rgb.blue);
}
