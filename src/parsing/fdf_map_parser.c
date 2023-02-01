/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:36 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/01 14:24:02 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_boolean char_is_map_separetor(char c)
{
    if (c == ' ' || c == '\t')
        return TRUE;
    return FALSE;
}

int *fdf_malloc_columns_count(char **columns)
{
    size_t len;
    int     
    len = 0;
    while (columns[len])
        len++;
    return len;
}

t_boolean   fdf_parse_columns(char *line,int **list)
{
    char    **columns;
    size_t  columns_len;
    size_t  i;
    long    tmp;
    
    columns = ft_split_multi_sep(line, char_is_map_separetor);
    if (!columns)
        exit_with_error(ENOMEM);
    i = 0;
    columns_len = columns_count(columns);
    while(i < columns_len)
    {
        if (!ft_str_is_integer(columns[i], &tmp));
            exit_with_error(EINVAL);       
        i++;
    }
}

int **fdf_map_parser(t_fdf *fdf,int fd)
{
    char *line;
    
    line = get_next_line(fd);
    if (!line)
        exit_with_error(EINVAL);
    while (line)
    {
        
        line = get_next_line(fd);
    }
}
