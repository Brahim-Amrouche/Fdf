/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:53:33 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/16 20:42: by bamrouch         ###   ########.fr       */
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

# define ESC_KEY 53
# define D_KEY 2
# define A_KEY 0
# define W_KEY 13
# define S_KEY 1
# define P_KEY 35
# define C_KEY 8
# define RIGHT_KEY 124
# define LEFT_KEY 123
# define UP_KEY 126
# define DOWN_KEY 125
# define FORWARD_SCROLL 5
# define BACKWARDS_SCROLL 4
# define LEFT_CLIC 1
# define RIGHT_CLIC 2

# define N_COLOR1 0x39B5E0
# define N_COLOR2 0xA31ACB

# define RED_SHADE 0xFF0000
# define GREEN_SHADE 0x00FF00
# define BLUE_SHADE 0x0000FF

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
	int				rot_start[2];
	int				neon_step;
	double			zoom;
	double			horizontal_offset;
	double			vertical_offset;
	double			perspective_angle;
	double			rot_z;
	double			rot_x;
	double			rot_y;
	t_boolean		activate_rot;
	t_boolean		isometric_projection;
	t_boolean		color_in_neon;
	t_point_specs	**specs;
	t_point			**projected_points;
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
char				**ft_split_multi_sep(char *s,
						t_boolean (*sep_checker)(char));

// hooks
//fdf_hooks_helper.c
int					rotate_hook(int x, int y, t_fdf *fdf);
int					mouse_release_hook(int button, int x, int y, t_fdf *fdf);
//fdf_hook.c
void				fdf_hooks(t_fdf *fdf);

// parsing

//fdf_projection.c
void				fdf_malloc_projected_points(t_fdf *fdf);
t_point				**fdf_project_all_points(t_fdf *fdf);
//fdf_map_parser.c
void				fdf_map_parser(t_fdf *fdf, int fd);
t_point				fdf_project_point(t_fdf *fdf, t_point p);

//parser.c
void				fdf_parser(t_fdf *fdf, int input_count,
						char *input_value[]);

// rasterisation
///fdf_color_fade.c
void				fdf_split_rgb(unsigned int color, t_rgb *p_rgb);
int					fdf_color_opacity(unsigned int color, double grad);
int					fdf_fade_color(t_point *p1, t_point *p2,
						int distance_passed);
//fdf_neon_color.c
unsigned int		fdf_neon_color_move(t_point *p, int y_count, int neon_step);

// fdf_pixel_put.c
void				fdf_pixel_put(t_fdf *fdf, int x, int y, int color);
// fdf_draw_line.c
void				fdf_draw_line(t_fdf *fdf, t_point *p1, t_point *p2);

// perspectives
//draw_fdf.c
t_boolean			draw_fdf(t_fdf *fdf);
// isometric_view.c
t_point				isometric_view(t_fdf *fdf, t_point p);
// parallel_view.c
t_point				parallel_view(t_fdf *fdf, t_point p);
// fdf_rotation.c
void				fdf_rotate_points(t_fdf *fdf, t_point *p);

//exit_fdf.c
void				exit_fdf(t_fdf *fdf, int errn, char *message,
						t_boolean is_error);

//init_mlx.c
void				fdf_mlx_init(t_fdf *fdf);
void				fdf_mlx_init_window(t_fdf *fdf);
void				fdf_mlx_init_image(t_fdf *fdf);

// X11 Event Masks
# define NOEVENTMASK 0L
# define KEYPRESSMASK 1L
# define BUTTONPRESSMASK 4L
# define BUTTONRELEASEMASK 8L
# define POINTERMOTIONMASK 64L

// X11 Event Names

# define KEYPRESS 2
# define BUTTONPRESS 4
# define BUTTONRELEASE 5
# define MOTIONNOTIFY 6
# define DESTROYNOTIFY 17

#endif