/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:36 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/01 20:48:47 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_boolean char_is_map_separetor(char c)
{
    if (c == ' ' || c == '\t')
        return TRUE;
    return FALSE;
}

static void fdf_resize_rows_array(int ***rows,int *columns)
{
	size_t i;
	size_t rows_len;
	int **new_rows;

	rows_len = 0;
	if (*rows)
		rows_len = (*rows)[0][0];
	new_rows = ft_malloc(sizeof(int *) * (rows_len + 1),(t_mem_manage_params) {NULL, rows_len + 4, NULL,0});
	if (!new_rows)
		exit_with_error(ENOMEM);
	i = 0;
	while (i < rows_len)
	{
		new_rows[i] = (*rows)[i];
		i++;
	}
	new_rows[i] = columns;
	ft_free(rows_len + 3, FALSE);
	new_rows[0][0]= rows_len + 1;
	*rows = new_rows;
}

static int *fdf_malloc_columns_array(char **columns, int ***rows)
{
    size_t	len;
	int		*columns_array;

	if (!*rows)
	{
		columns_array = ft_malloc(sizeof(int), (t_mem_manage_params){NULL, 1, NULL, 0});
		if (!columns)
			exit_with_error(ENOMEM);
		columns_array[0] = 0;
		fdf_resize_rows_array(rows, columns_array);
	}
	len = 0;
	while (columns[len])
        len++;
	columns_array = ft_malloc(sizeof(int) * (len + 1), (t_mem_manage_params){NULL, 1, *(rows)[0], 0});
	if (!columns_array)
		exit_with_error(ENOMEM);
	columns_array[0] = len + 1;
	fdf_resize_rows_array(rows, columns_array);
	return columns_array;
}

static void	fdf_parse_columns(char *line,int ***rows)
{
    char    **columns;
    int		*columns_array;
    ssize_t  i;
    long    tmp;
    
    columns = ft_split_multi_sep(line, char_is_map_separetor);
	free(line);
	if (!columns)
		exit_with_error(ENOMEM);
    i = 1;
    columns_array = fdf_malloc_columns_array(columns, rows);
    while(i < columns_array[0])
    {
        if (!ft_str_is_integer(columns[i - 1], &tmp))
            exit_with_error(EINVAL);
		columns_array[i] = tmp;
		i++;
	}
	ft_free(2, FALSE);
}

void	fdf_map_parser(t_fdf *fdf,int fd)
{
    char *line;
	int	 **rows;

	line = get_next_line(fd);
    if (!line)
        exit_with_error(EINVAL);
	rows = NULL;
	while (line)
	{
		fdf_parse_columns(line, &rows);
		line = get_next_line(fd);
	}
	fdf->map = rows;
}
