/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:53:33 by bamrouch          #+#    #+#             */
/*   Updated: 2023/01/29 16:38:53 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H
#include "ft_garbage_collector.h"
#include <mlx.h>

typedef struct s_frame_data
{
    void	*img;
    char	*addr;
    int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_frame_data;

typedef struct s_point
{
	int	x;
	int	y;
	int z;
}	t_point;

typedef struct s_block_info
{
    unsigned int	width;
    unsigned int	height;
	unsigned int	color;
} t_block_info;

typedef struct s_window_info
{
	unsigned int width;
	unsigned int height;
} t_window_info;

typedef struct s_fdf
{
    void			*mlx;
	void			*mlx_window;
    t_window_info	window_info;
	t_block_info	block_info;
	t_frame_data	frame;
}   t_fdf;

#endif