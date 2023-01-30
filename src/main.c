/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:48:56 by bamrouch          #+#    #+#             */
/*   Updated: 2023/01/30 20:18:55 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	unsigned int	*dst;

	dst = (unsigned int *) fdf->frame.addr;
	if (x >= 0 && (unsigned int)x < fdf->window_info.width && y >= 0 && (unsigned int)y < fdf->window_info.height )
		dst[x + (y * fdf->window_info.width)] = (unsigned int) color;
}

double degree_to_rad(int degree)
{
	return degree *((float) M_PI) / 180.0F;
}

t_point	isometric_view(t_fdf *fdf, t_point p)
{
	int angle;
	int angle2;
	int x;
	t_point res;

	angle2 = 0;
	angle = 30;
	p.x *= fdf->block_info.width;
	p.y *= fdf->block_info.height;
	p.z *= 4;
	res.x = p.x * cos(degree_to_rad(90 + 2 * angle)) + p.y * cos(degree_to_rad(angle)) + p.z * sin(degree_to_rad(-30 + angle));
	res.y = p.x * sin(degree_to_rad(90 + 2 * angle)) + p.y * sin(degree_to_rad(angle)) - p.z * cos(degree_to_rad(-30 + angle));
	x = res.x * cos(degree_to_rad(angle2)) + res.y * sin(degree_to_rad(angle2));
	res.y = - res.x * sin(degree_to_rad(angle2)) + res.y * cos(degree_to_rad(angle2));
	res.x = x;
	res.x += fdf->window_info.width / 2;
	res.y += fdf->window_info.height / 2;
	my_mlx_pixel_put(fdf, res.x, res.y, fdf->block_info.color);
	return res;
}


void	fdf_draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	
	t_point tmp[2];
	double	grad;
	double	y;
	tmp[0] = p1;
	tmp[1] = p2;
	
	if (tmp[0].x > tmp[1].x)
	{
		tmp[0] = p2;
		tmp[1] = p1;
	}
	y = (double) tmp[0].y;
	grad = tmp[1].x - tmp[0].x ? 20 * (double)(tmp[1].y - tmp[0].y) / (double)(tmp[1].x - tmp[0].y) : 1;
	while (tmp[0].x < tmp[1].x)
	{
		my_mlx_pixel_put(fdf, tmp[0].x, y, fdf->block_info.color);
		my_mlx_pixel_put(fdf, tmp[0].x, y - 1, fdf->block_info.color);
		y += grad;
		tmp[0].x++;
	}
}

void	fdf_draw_block(t_fdf *fdf, t_point p1 ,t_point p2)
{
	
	p1 = isometric_view(fdf, p1);
	p2 = isometric_view(fdf, p2);

	fdf_draw_line(fdf, p1, p2);
}


void	fdf_put_block(t_fdf *fdf)
{
	unsigned int	x;
	unsigned int	y;

	
	x = 0;
	while (x <= 10)
	{	
		y = 0;
		while (y <= 10)
		{	
			isometric_view(fdf, (t_point){x, y, 0});
			// if (x > 0)
			// 	fdf_draw_block(fdf, (t_point){x, y, 0}, (t_point){x - 1, y, 0});
			// if (y > 0)
			// 	fdf_draw_block(fdf, (t_point){x , y, 0}, (t_point){x , y-1, 0});
			y++;
		}
		x++;
	}
	
	// t_point tmp1 = isometric_view(fdf, (t_point){0, 0,0});
	// t_point tmp2 = isometric_view(fdf, (t_point){4, 0,0});
	// ft_printf("tmp 1[%d] [%d]\n", tmp1.x, tmp1.y);
	// ft_printf("tmp 2[%d] [%d]\n", tmp2.x, tmp2.y);
	// fdf_draw_line(fdf, tmp2 ,tmp1);
}

int main()
{
	t_fdf	fdf;

	ft_bzero(&fdf,sizeof(fdf));
	fdf.mlx = mlx_init();
	fdf.window_info =(t_window_info) {1920, 1080};
	fdf.block_info = (t_block_info) {20, 30,0x00FFFFFF};
	fdf.mlx_window = mlx_new_window(fdf.mlx, fdf.window_info.width, fdf.window_info.height, "Hello world!");
	fdf.frame.img = mlx_new_image(fdf.mlx, fdf.window_info.width, fdf.window_info.height);
	fdf.frame.addr = mlx_get_data_addr(fdf.frame.img, &fdf.frame.bits_per_pixel, &fdf.frame.line_length,
							&fdf.frame.endian);		
	fdf_put_block(&fdf);
	mlx_put_image_to_window(fdf.mlx, fdf.mlx_window, fdf.frame.img, 0, 0);
	mlx_loop(fdf.mlx);
}