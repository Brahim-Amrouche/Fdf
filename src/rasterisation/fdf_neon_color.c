/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_neon_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:55:52 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/16 20:19:48 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fdf_neon_color_move(t_point *p1, t_point *p2)
{
	t_rgb	p_rgb;
	t_rgb	color1_rgb;
	t_rgb	color2_rgb;
	double	ratio;

	fdf_split_rgb(p1->specs.color, &p_rgb);
	fdf_split_rgb(N_COLOR1, &color1_rgb);
	fdf_split_rgb(N_COLOR2, &color2_rgb);
	ratio = (double)(color2_rgb.red - color1_rgb.red) / p2->x;
	p_rgb.red += (double)ratio * p1->x;
	ratio = (double)(color2_rgb.green - color1_rgb.green) / p2->x;
	p_rgb.green += (double)ratio * p1->x;
	ratio = (double)(color2_rgb.blue - color1_rgb.blue) / p2->x;
	p_rgb.blue += (double)ratio * p1->x;
	return ((p_rgb.red << 16) + (p_rgb.green << 8) + p_rgb.blue);
}

static void	fdf_malloc_neon_colors(t_fdf *fdf)
{
	int i;
	
	fdf->map.neon_specs = ft_malloc(fdf->map.y_count * sizeof(t_point_specs *),(t_mem_manage_params) {NULL, 1, 0, 0});
	if (!fdf->map.neon_specs)
		exit_fdf(fdf, ENOMEM, "\tcouldnt malloc neon colors 2D array", TRUE);
	i = 0;
	while (i < fdf->map.y_count)
	{
		fdf->map.neon_specs[i] = ft_malloc(fdf->map.x_count * sizeof(t_point_specs),(t_mem_manage_params){NULL, 1, fdf->map.neon_specs, 0});
		if (!fdf->map.neon_specs[i])
			exit_fdf(fdf, ENOMEM, "\tcouldnt malloc a neon colors row", TRUE);
		i++;
	}
}

void fdf_switch_neon(t_fdf *fdf)
{
	void *temp;

	if (!fdf->map.neon_specs)
		fdf_neon_color(fdf);
	fdf->map.color_in_neon = !fdf->map.color_in_neon;
	temp = fdf->map.specs;
	fdf->map.specs = fdf->map.neon_specs;
	fdf->map.neon_specs = (t_point_specs **) temp;
}

void	fdf_neon_color(t_fdf *fdf)
{
	t_point	p1;
	t_point	p2;

	p2.x = fdf->map.x_count;
	p2.y = fdf->map.y_count;
	p1.x = 0;
	p1.specs.color = N_COLOR1;
	fdf_malloc_neon_colors(fdf);
	while (p1.x < p2.x)
	{
		p1.y = 0;
		while (p1.y < p2.y)
		{
			fdf->map.neon_specs[p1.y][p1.x].color = fdf_neon_color_move(&p1, &p2);
			fdf->map.neon_specs[p1.y][p1.x].z = fdf->map.specs[p1.y][p1.x].z;
			p1.y++;
		}
		p1.x++;
	}
}
