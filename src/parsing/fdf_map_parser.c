/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:36 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/16 18:46:39 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_boolean	char_is_map_separetor(char c)
{
	if (c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}

static void	fdf_resize_rows_array(t_fdf *fdf, t_point_specs ***rows,
		t_point_specs *columns)
{
	int				i;
	t_point_specs	**new_rows;

	new_rows = ft_malloc(sizeof(t_point_specs *) * (fdf->map.y_count + 1),
			(t_mem_manage_params){NULL, fdf->map.y_count + 4, NULL, 0});
	if (!new_rows)
		exit_with_error(ENOMEM, "\tcouldn't malloc rows");
	i = 0;
	while (i < fdf->map.y_count)
	{
		new_rows[i] = (*rows)[i];
		i++;
	}
	new_rows[i] = columns;
	ft_free(fdf->map.y_count + 3, FALSE);
	fdf->map.y_count++;
	*rows = new_rows;
}

static void	fdf_malloc_columns_array(t_fdf *fdf, char **columns,
		t_point_specs ***rows)
{
	int				len;
	t_point_specs	*columns_array;

	len = 0;
	while (columns[len])
		len++;
	if (fdf->map.y_count == 0)
		columns_array = ft_malloc(sizeof(t_point_specs) * len,
				(t_mem_manage_params){NULL, 1, NULL, 0});
	else
		columns_array = ft_malloc(sizeof(t_point_specs) * len,
				(t_mem_manage_params){NULL, 1, (*rows)[0], 0});
	if (!columns_array)
		exit_with_error(ENOMEM, "\tcouldn't malloc columns number array");
	fdf_resize_rows_array(fdf, rows, columns_array);
	if (fdf->map.y_count > 1 && len != fdf->map.x_count)
		exit_with_error(EINVAL, "\t uneven rows");
	fdf->map.x_count = len;
}

static void	fdf_parse_columns(t_fdf *fdf, char *line, t_point_specs ***rows)
{
	char	**columns;
	int		i;
	int		tmp;

	columns = ft_split_multi_sep(line, char_is_map_separetor);
	free(line);
	if (!columns)
		exit_with_error(ENOMEM, "\tcouldn't split the input");
	i = 0;
	fdf_malloc_columns_array(fdf, columns, rows);
	while (i < fdf->map.x_count)
	{
		if (!ft_str_is_integer(columns[i], &tmp))
			exit_with_error(EINVAL, "\tnot all inputs are numbers");
		if (fdf->map.y_count == 1 || fdf->map.heighest_point < ft_abs(tmp))
			fdf->map.heighest_point = ft_abs(tmp);
		((*rows)[fdf->map.y_count - 1][i]).z = tmp;
		if (!ft_str_is_hex(columns[i], &tmp))
			exit_with_error(EINVAL, "\thex value must be well formated");
		((*rows)[fdf->map.y_count - 1][i]).color = (unsigned int)tmp;
		i++;
	}
	ft_free(2, FALSE);
}

void	fdf_map_parser(t_fdf *fdf, int fd)
{
	char			*line;
	t_point_specs	**rows;
	size_t			line_len;

	line = get_next_line(fd);
	if (!line)
		exit_with_error(EINVAL, "\tcouldn't read the first line");
	rows = NULL;
	while (line)
	{
		line_len = strlen(line) - 1;
		if (line[line_len] == '\n')
			line[line_len] = 0;
		fdf_parse_columns(fdf, line, &rows);
		line = get_next_line(fd);
	}
	fdf->map.specs = rows;
	mem_manage_move((t_mem_manage_params){NULL, fdf->map.y_count + 3, rows, 1});
	ft_free(fdf->map.y_count + 3, FALSE);
}
