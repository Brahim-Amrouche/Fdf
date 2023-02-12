/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:47:44 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/12 16:10:11 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	exit_hook(int keycode, t_fdf *fdf)
{
    (void ) fdf;
    ft_printf("hello [%d]\n",keycode);
    return 0;   
}


void	fdf_hooks(t_fdf *fdf)
{
    mlx_hook(fdf->mlx_window, KeyRelease, KeyReleaseMask, exit_hook, fdf);
}

