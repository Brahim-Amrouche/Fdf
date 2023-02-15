/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:48:56 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/15 16:46:09 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_fdf	fdf;

	ft_bzero(&fdf, sizeof(fdf));
	fdf_parser(&fdf, argc, argv);
	fdf_mlx_init(&fdf);
	fdf_neon_color(&fdf);
	draw_fdf(&fdf);
	mlx_loop(fdf.mlx);
}
