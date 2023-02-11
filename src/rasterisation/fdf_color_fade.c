/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color_fade.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:57:53 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/11 15:53:57 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define RED_SHADE 0xFF0000
#define GREEN_SHADE 0x00FF00
#define BLUE_SHADE 0x0000FF

static int fdf_rgb_fade(double color_shade_diff, double total_distance, int distance_passed)
{
	return (color_shade_diff / total_distance) * distance_passed;
}

static int	fdf_rgb_picker(unsigned int color, int shade,int shift)
{
	return (color & shade) >> shift;
}

int fdf_color_opacity(unsigned int color, double grad)
{
    unsigned int opacity;

    opacity = (int) (0xFF * grad) ;   
    color = (color | (opacity << 24));
    return color;
}

int	fdf_fade_color(t_point *p1, t_point *p2, int distance_passed)
{
    int total_distance;
    t_rgb p1_rgb;
    t_rgb p2_rgb;

    total_distance = p2->x - p1->x;
    p1_rgb.red = fdf_rgb_picker(p1->specs.color, RED_SHADE, 16);
    p2_rgb.red = fdf_rgb_picker(p2->specs.color, RED_SHADE, 16);
    p1_rgb.green = fdf_rgb_picker(p1->specs.color, GREEN_SHADE, 8);
    p2_rgb.green = fdf_rgb_picker(p2->specs.color, GREEN_SHADE, 8);
    p1_rgb.blue = fdf_rgb_picker(p1->specs.color, BLUE_SHADE, 0);
    p2_rgb.blue = fdf_rgb_picker(p1->specs.color, BLUE_SHADE, 0);
    p1_rgb.red += fdf_rgb_fade(p2_rgb.red - p1_rgb.red , total_distance, distance_passed);
    p1_rgb.green += fdf_rgb_fade(p2_rgb.green - p1_rgb.green , total_distance, distance_passed);
	p1_rgb.blue += fdf_rgb_fade(p2_rgb.blue - p1_rgb.blue , total_distance, distance_passed);
	return ((p1_rgb.red << 16) + (p1_rgb.green << 8) + p1_rgb.blue);
}