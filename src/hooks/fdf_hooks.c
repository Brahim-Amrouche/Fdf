/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:47:44 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/17 1 by bamrouch         ###   ########.fr       */
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
	return (0);
}

int	refresh(t_fdf *fdf)
{
	static int	fps;

	if (fps++ > 500)
	{
		fps = 0;
		draw_fdf(fdf);
	}
	return (0);
}

void	fdf_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->mlx_window, DESTROYNOTIFY, NOEVENTMASK, close_window, fdf);
	mlx_hook(fdf->mlx_window, KEYPRESS, KEYPRESSMASK, keyboard_hooks, fdf);
	mlx_loop_hook(fdf->mlx, refresh, fdf);
}
