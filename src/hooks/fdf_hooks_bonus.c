/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:49:54 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/19 14:12:25 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_fdf *fdf)
{
	exit_fdf(fdf, 0, NULL, FALSE);
	return (0);
}

int	keyboard_hooks(int keycode, t_fdf *fdf)
{
	if (keycode == ESC_KEY)
		exit_fdf(fdf, 0, NULL, FALSE);
	else if (keycode == DOWN_KEY || keycode == S_KEY)
		fdf->map.vertical_offset -= 0.03;
	else if (keycode == UP_KEY || keycode == W_KEY)
		fdf->map.vertical_offset += 0.03;
	else if (keycode == RIGHT_KEY || keycode == D_KEY)
		fdf->map.horizontal_offset -= 0.03;
	else if (keycode == LEFT_KEY || keycode == A_KEY)
		fdf->map.horizontal_offset += 0.03;
	else if (keycode == P_KEY)
		fdf->map.isometric_projection = !fdf->map.isometric_projection;
	else if (keycode == C_KEY)
		fdf->map.color_in_neon = !fdf->map.color_in_neon;
	return (0);
}

int	mouse_press_hook(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == BACKWARDS_SCROLL && fdf->map.zoom > 0.2)
		fdf->map.zoom -= 0.08;
	else if (button == FORWARD_SCROLL)
		fdf->map.zoom += 0.08;
	else if (button == LEFT_CLIC)
	{
		fdf->map.activate_rot = TRUE;
		fdf->map.rot_start[0] = x;
		fdf->map.rot_start[1] = y;
	}
	return (0);
}

int	refresh(t_fdf *fdf)
{
	static int	fps;

	if (fps++ > 500)
	{
		fps = 0;
		draw_fdf(fdf);
		if (fdf->map.color_in_neon
			&& fdf->map.neon_step++ > fdf->map.x_count)
			fdf->map.neon_step = 0;
	}
	return (0);
}

void	fdf_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->mlx_window, DESTROYNOTIFY, NOEVENTMASK, close_window, fdf);
	mlx_hook(fdf->mlx_window, KEYPRESS, KEYPRESSMASK, keyboard_hooks, fdf);
	mlx_hook(fdf->mlx_window, BUTTONPRESS, BUTTONPRESSMASK, mouse_press_hook,
		fdf);
	mlx_hook(fdf->mlx_window, MOTIONNOTIFY, POINTERMOTIONMASK, rotate_hook,
		fdf);
	mlx_hook(fdf->mlx_window, BUTTONRELEASE, BUTTONRELEASEMASK,
		mouse_release_hook, fdf);
	mlx_loop_hook(fdf->mlx, refresh, fdf);
}
