/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:19:49 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/19 16:36:55 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_fdf(t_fdf *fdf, int errn, char *message, t_boolean is_error)
{
	if (fdf->frame.img)
		mlx_destroy_image(fdf->mlx, fdf->frame.img);
	if (fdf->mlx_window)
		mlx_destroy_window(fdf->mlx, fdf->mlx_window);
	if (is_error)
		exit_with_error(errn, message);
	ft_free(0, TRUE);
	exit(EXIT_SUCCESS);
}
