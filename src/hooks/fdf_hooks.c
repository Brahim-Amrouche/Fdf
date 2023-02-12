/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:47:44 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/12 21:15:36 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define ESC_KEY 53
#define D_KEY   2
#define A_KEY   0
#define W_KEY   13
#define S_KEY   1
#define RIGHT_KEY 124
#define LEFT_KEY  123
#define UP_KEY    126
#define DOWN_KEY  125
#define FORWARD_SCROLL 5
#define BACKWARDS_SCROLL 4

int close_window(t_fdf *fdf)
{
    exit_fdf(fdf, 0, NULL, FALSE);
    return 0;
}

int	keyboard_hooks(int keycode, t_fdf *fdf)
{
    if (keycode == ESC_KEY)
        exit_fdf(fdf, 0, NULL, FALSE);
    if (keycode == DOWN_KEY || keycode == S_KEY)
        fdf->map.vertical_offset -= 0.03;
    if (keycode == UP_KEY || keycode == W_KEY)
        fdf->map.vertical_offset += 0.03;
    if (keycode == RIGHT_KEY || keycode == D_KEY)
        fdf->map.horizontal_offset -= 0.03;
    if (keycode == LEFT_KEY || keycode == A_KEY)
        fdf->map.horizontal_offset += 0.03;
    draw_fdf(fdf);
    return 0;   
}

int mouse_press_hook(int button, int x, int y, t_fdf *fdf)
{
    (void) x;
    (void) y;
    if (button == BACKWARDS_SCROLL && fdf->map.zoom > 0.2)
        fdf->map.zoom -= 0.08;
    if (button == FORWARD_SCROLL)
        fdf->map.zoom += 0.08;
    draw_fdf(fdf);
    return 0;
}

void	fdf_hooks(t_fdf *fdf)
{
    mlx_hook(fdf->mlx_window, DestroyNotify, NoEventMask, close_window, fdf);
    mlx_hook(fdf->mlx_window,  KeyPress, KeyPress, keyboard_hooks, fdf);
    mlx_hook(fdf->mlx_window,  ButtonPress,  ButtonPressMask, mouse_press_hook, fdf);
    // mlx_hook(fdf->mlx_window,  ButtonRelease,  ButtonReleaseMask, mouse_hooks, fdf);
}

