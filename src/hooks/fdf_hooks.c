/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:47:44 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/12 19:30:22 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define ESC_KEY 53
#define FORWARD_SCROLL 5
#define BACKWARDS_SCROLL 4

int close_window(t_fdf *fdf)
{
    exit_fdf(fdf, 0, NULL, FALSE);
    return 0;
}

int	exit_hook(int keycode, t_fdf *fdf)
{
    if (keycode == ESC_KEY)
        exit_fdf(fdf, 0, NULL, FALSE);
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
    mlx_hook(fdf->mlx_window, DestroyNotify, KeyPressMask, close_window, fdf);
    mlx_hook(fdf->mlx_window,  KeyRelease, KeyRelease, exit_hook, fdf);
    mlx_hook(fdf->mlx_window,  ButtonPress,  ButtonPressMask, mouse_press_hook, fdf);
    // mlx_hook(fdf->mlx_window,  ButtonRelease,  ButtonReleaseMask, mouse_hooks, fdf);
}

