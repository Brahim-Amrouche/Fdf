/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:53:33 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/01 18:55:51 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "ft_garbage_collector.h"
# include <mlx.h>
# include <errno.h>
# define FRAME_WIDTH 1920
# define FRAME_HEIGHT 1080

typedef struct s_frame_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_frame_data;

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
}					t_point;

typedef struct s_block_info
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	color;
}					t_block_info;

typedef struct s_window_info
{
	unsigned int	width;
	unsigned int	height;
}					t_window_info;

typedef struct s_fdf
{
	void			*mlx;
	void			*mlx_window;
	t_window_info	window_info;
	t_block_info	block_info;
	t_frame_data	frame;
	int				**map;
} t_fdf;

//helpers
//math.c
double				degree_to_rad(int degree);
int					ft_abs(int x);
t_boolean			ft_str_is_integer(const char *str, long *res);
//utils.c
void				pointer_swap(void **a, void **b);
void				int_swap(int *a, int *b);
void				exit_with_error(int errn);
//split_util.c
char				**ft_split_multi_sep(char *s,
						t_boolean (*sep_checker)(char));

// parsing
//fdf_map_parser.c
void				fdf_map_parser(t_fdf *fdf, int fd);

//parser.c
void				fdf_parser(t_fdf *fdf, int input_count, char *input_value[]);

// rasterisation
// fdf_pixel_put.c
void				fdf_pixel_put(t_fdf *fdf, int x, int y, int color);
// fdf_draw_line.c
void				fdf_draw_line(t_fdf *fdf, t_point *p1, t_point *p2);

// perspectives
//draw_fdf.c
void				draw_fdf(t_fdf *fdf);
// isometric_view.c
t_point				isometric_view(t_fdf *fdf, t_point p);

//init_fdf.c
t_boolean			fdf_init(t_fdf *fdf);

#endif