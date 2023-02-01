/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:48:56 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/01 18:00:12 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char *argv[])
{
	t_fdf	fdf;

	ft_bzero(&fdf,sizeof(fdf));
	fdf_parser(&fdf, argc, argv);
	fdf_init(&fdf);
	draw_fdf(&fdf);
	mlx_loop(fdf.mlx);
}