/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color_fade.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:57:53 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/15 19:46:42 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define RED_SHADE 0xFF0000
#define GREEN_SHADE 0x00FF00
#define BLUE_SHADE 0x0000FF

static int	fdf_rgb_fade(double color_shade_diff, double total_distance,
		int distance_passed)
{
	return ((color_shade_diff / total_distance) * distance_passed);
}

static int	fdf_rgb_picker(unsigned int color, int shade, int shift)
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

int	fdf_fade_color(t_point *p1, t_point *p2, int distance_passed)
{
	int		total_distance;
	t_rgb	p1_rgb;
	t_rgb	p2_rgb;

	total_distance = p2->x - p1->x;
	p1_rgb.red = fdf_rgb_picker(p1->specs.color, RED_SHADE, 16);
	p2_rgb.red = fdf_rgb_picker(p2->specs.color, RED_SHADE, 16);
	p1_rgb.green = fdf_rgb_picker(p1->specs.color, GREEN_SHADE, 8);
	p2_rgb.green = fdf_rgb_picker(p2->specs.color, GREEN_SHADE, 8);
	p1_rgb.blue = fdf_rgb_picker(p1->specs.color, BLUE_SHADE, 0);
	p2_rgb.blue = fdf_rgb_picker(p2->specs.color, BLUE_SHADE, 0);
	p1_rgb.red += fdf_rgb_fade(p2_rgb.red - p1_rgb.red, total_distance,
			distance_passed);
	p1_rgb.green += fdf_rgb_fade(p2_rgb.green - p1_rgb.green, total_distance,
			distance_passed);
	p1_rgb.blue += fdf_rgb_fade(p2_rgb.blue - p1_rgb.blue, total_distance,
			distance_passed);
	return ((p1_rgb.red << 16) + (p1_rgb.green << 8) + p1_rgb.blue);
}

#define N_COLOR1 0x39B5E0
#define N_COLOR2 0xA31ACB
#define n_color1_red ((N_COLOR1 & RED_SHADE) >> 16)
#define n_color1_green ((N_COLOR1 & GREEN_SHADE) >> 8)
#define n_color1_blue (N_COLOR1 & BLUE_SHADE)
#define n_color2_red ((N_COLOR2 & RED_SHADE) >> 16)
#define n_color2_green ((N_COLOR2 & GREEN_SHADE) >> 8)
#define n_color2_blue (N_COLOR1 & BLUE_SHADE)

int		fdf_neon_color_move(t_point *p1 , t_point *p2)
{
	t_rgb	p1_rgb;
	double  ratio;
	
	p1_rgb.red = fdf_rgb_picker(p1->specs.color, RED_SHADE, 16);
	p1_rgb.green = fdf_rgb_picker(p1->specs.color, GREEN_SHADE, 8);
	p1_rgb.blue = fdf_rgb_picker(p1->specs.color, BLUE_SHADE, 0);

	ratio = (double) (n_color2_red -  n_color1_red) / p2->x ;
	if ((ratio < 0 && p1_rgb.red > n_color2_red ) || (ratio > 0 && p1_rgb.red < n_color2_red ))
		p1_rgb.red += (double) ratio * p1->x;
	ratio = (double) (n_color2_green -  n_color1_green) / p2->x ;
	if ((ratio < 0 && p1_rgb.green > n_color2_green) || (ratio > 0 && p1_rgb.green < n_color2_green))
		p1_rgb.green += (double) ratio * p1->x;
	ratio = (double) (n_color2_blue -  n_color1_blue) / p2->x ;
	if ((ratio < 0 && p1_rgb.blue > n_color2_blue) ||  (ratio > 0 && p1_rgb.blue < n_color2_blue))
		p1_rgb.blue += (double) ratio * p1->x;
	return ((p1_rgb.red << 16) + (p1_rgb.green << 8) + p1_rgb.blue);
}


void	fdf_neon_color(t_fdf *fdf)
{
	t_point p1;
	t_point p2;
	
	p2.x = fdf->map.x_count;
	p2.y = fdf->map.y_count;
	p1.x = 0;
	p1.specs.color = N_COLOR1;
	while (p1.x < p2.x)
	{
		p1.y = 0;
		while (p1.y < p2.y)
		{
			fdf->map.specs[p1.y][p1.x].color = fdf_neon_color_move(&p1, &p2);
			p1.y++;
		}
		p1.x++;
	}
}
