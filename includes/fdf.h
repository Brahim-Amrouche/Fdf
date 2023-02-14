/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:53:33 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/14 19:13:45 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "ft_garbage_collector.h"
# include <errno.h>
# include <math.h>
# include <mlx.h>

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

typedef struct s_rgb
{
	int				red;
	int				green;
	int				blue;
}					t_rgb;

typedef struct s_point_specs
{
	int				z;
	unsigned int	color;
}					t_point_specs;

typedef struct s_point
{
	int				x;
	int				y;
	t_point_specs	specs;
}					t_point;

typedef struct s_map
{
	int				x_count;
	int				y_count;
	int				heighest_point;
	int				z_scale;
	double			zoom;
	double			horizontal_offset;
	double			vertical_offset;
	double			rot_angle;
	t_boolean		isometric_projection;
	t_point_specs	**specs;
}					t_map;

typedef struct s_block_info
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	default_color;
}					t_block_info;

typedef struct s_window_info
{
	int				width;
	int				height;
}					t_window_info;

typedef struct s_fdf
{
	void			*mlx;
	void			*mlx_window;
	t_window_info	window_info;
	t_block_info	block_info;
	t_frame_data	frame;
	t_map			map;
}					t_fdf;

//helpers
//hex_helpers.c
t_boolean			ft_str_is_hex(char *str, int *res);
//math.c
double				degree_to_rad(int degree);
int					ft_abs(int x);
double				floating_point(double x);
t_boolean			ft_str_is_integer(const char *str, int *res);
//utils.c
void				pointer_swap(void **a, void **b);
void				int_swap(int *a, int *b);
void				exit_with_error(int errn, char *message);
//split_util.c
char	**ft_split_multi_sep(char *s,
							t_boolean (*sep_checker)(char));

// hooks
//fdf_hook.c
void				fdf_hooks(t_fdf *fdf);

// parsing
//fdf_map_parser.c
void				fdf_map_parser(t_fdf *fdf, int fd);

//parser.c
void				fdf_parser(t_fdf *fdf, int input_count,
						char *input_value[]);

// rasterisation
///fdf_color_fade.c
int					fdf_color_opacity(unsigned int color, double grad);
int					fdf_fade_color(t_point *p1, t_point *p2,
						int distance_passed);
// fdf_pixel_put.c
void				fdf_pixel_put(t_fdf *fdf, int x, int y, int color);
// fdf_draw_line.c
void				fdf_draw_line(t_fdf *fdf, t_point *p1, t_point *p2);

// perspectives
//draw_fdf.c
int					draw_fdf(t_fdf *fdf);
// isometric_view.c
t_point				isometric_view(t_fdf *fdf, t_point p);
// parallel_view.c
t_point				parallel_view(t_fdf *fdf, t_point p);

//exit_fdf.c
void				exit_fdf(t_fdf *fdf, int errn, char *message,
						t_boolean is_error);

//init_mlx.c
void				fdf_mlx_init(t_fdf *fdf);
void				fdf_mlx_init_window(t_fdf *fdf);
void				fdf_mlx_init_image(t_fdf *fdf);

// X11 Event Masks
# define NoEventMask 0L
# define KeyPressMask (1L << 0)
# define KeyReleaseMask (1L << 1)
# define ButtonPressMask (1L << 2)
# define ButtonReleaseMask (1L << 3)
# define EnterWindowMask (1L << 4)
# define LeaveWindowMask (1L << 5)
# define PointerMotionMask (1L << 6)
# define PointerMotionHintMask (1L << 7)
# define Button1MotionMask (1L << 8)
# define Button2MotionMask (1L << 9)
# define Button3MotionMask (1L << 10)
# define Button4MotionMask (1L << 11)
# define Button5MotionMask (1L << 12)
# define ButtonMotionMask (1L << 13)
# define KeymapStateMask (1L << 14)
# define ExposureMask (1L << 15)
# define VisibilityChangeMask (1L << 16)
# define StructureNotifyMask (1L << 17)
# define ResizeRedirectMask (1L << 18)
# define SubstructureNotifyMask (1L << 19)
# define SubstructureRedirectMask (1L << 20)
# define FocusChangeMask (1L << 21)
# define PropertyChangeMask (1L << 22)
# define ColormapChangeMask (1L << 23)
# define OwnerGrabButtonMask (1L << 24)

// X11 Event Names

# define KeyPress 2
# define KeyRelease 3
# define ButtonPress 4
# define ButtonRelease 5
# define MotionNotify 6
# define EnterNotify 7
# define LeaveNotify 8
# define FocusIn 9
# define FocusOut 10
# define KeymapNotify 11
# define Expose 12
# define GraphicsExpose 13
# define NoExpose 14
# define VisibilityNotify 15
# define CreateNotify 16
# define DestroyNotify 17
# define UnmapNotify 18
# define MapNotify 19
# define MapRequest 20
# define ReparentNotify 21
# define ConfigureNotify 22
# define ConfigureRequest 23
# define GravityNotify 24
# define ResizeRequest 25
# define CirculateNotify 26
# define CirculateRequest 27
# define PropertyNotify 28
# define SelectionClear 29
# define SelectionRequest 30
# define SelectionNotify 31
# define ColormapNotify 32
# define ClientMessage 33
# define MappingNotify 34
# define GenericEvent 35
# define LASTEvent 36

#endif