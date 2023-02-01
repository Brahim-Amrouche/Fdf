/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:38:11 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/01 13:26:47 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_boolean   fdf_input_is_valid_file_name(char *file_name)
{
    size_t file_name_len;
    char *file_ext;
    file_name_len = ft_strlen(file_name);
    if (file_name_len < 5)
        return FALSE;
    file_ext = &(file_name[file_name_len -  4]);
    if (ft_strncmp(file_ext, ".fdf", 4))
        return FALSE;
    return TRUE;
}

void    fdf_parser(t_fdf *fdf, int input_count, char *input_value[])
{
    int fd;
    (void) fdf;
    if (!(input_count == 2 && fdf_input_is_valid_file_name(input_value[1])))
        exit_with_error(EINVAL);
    fd = open(input_value[1],O_RDONLY);
    if (fd < 0)
        exit_with_error(ENOENT);
    close(fd);
    return TRUE;
}