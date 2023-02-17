/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:07:23 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/17 20:12:10 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_malloc_projected_points(t_fdf *fdf)
{
	int		i;
	t_point	**res;

	res = ft_malloc(sizeof(t_point *) * fdf->map.y_count,
			(t_mem_manage_params){NULL, 1, NULL, 0});
	if (!res)
		exit_fdf(fdf, ENOMEM, "\tcouldnt malloc projected points 2D array",
			TRUE);
	i = 0;
	while (i < fdf->map.y_count)
	{
		res[i] = ft_malloc(sizeof(t_point) * fdf->map.x_count,
				(t_mem_manage_params){NULL, 1, res, 0});
		if (!res)
			exit_fdf(fdf, ENOMEM, "\tcouldnt malloc projected points rows",
				TRUE);
		i++;
	}
	fdf->map.projected_points = res;
}

t_point	**fdf_project_all_points(t_fdf *fdf)
{
	int		i;
	int		j;
	t_point	*p;

	i = -1;
	while (++i < fdf->map.y_count)
	{
		j = -1;
		while (++j < fdf->map.x_count)
		{
			fdf->map.projected_points[i][j] = (t_point){i, j,
				fdf->map.specs[i][j]};
			p = &(fdf->map.projected_points[i][j]);
			if (fdf->map.color_in_neon)
				p->specs.color = fdf_neon_color_move(p, fdf->map.y_count,
						fdf->map.neon_step);
			*p = fdf_project_point(fdf, *p);
		}
		if (fdf->map.color_in_neon && fdf->map.neon_step++ > fdf->map.y_count)
			fdf->map.neon_step = 0;
	}
	return (fdf->map.projected_points);
}
