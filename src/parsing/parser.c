/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:38:11 by bamrouch          #+#    #+#             */
/*   Updated: 2023/02/11 19:59:22 by bamrouch         ###   ########.fr       */
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

static void     fdf_init_block_info(t_fdf *fdf, int input_count, char *input_value[])
{
    int block_size;
    int default_color;
    
    if (input_count >= 3)
    {
        if (!ft_str_is_integer(input_value[2], &block_size) || block_size <= 0)
            exit_with_error(EINVAL,"\tinvalid block size");
        if (!ft_str_is_hex(input_value[2], &default_color))
            exit_with_error(EINVAL,"\tinvalid block color format");
        if (!default_color)
            default_color = 0xFFFFFF; 
        fdf->block_info = (t_block_info) {block_size, block_size, default_color};
    }
    else 
    {
        block_size = log(10 + fdf->map.x_count * fdf->map.y_count);
        fdf->block_info = (t_block_info) {block_size , block_size, 0xFFFFFF};
        if (block_size <= 5)
            fdf->block_info = (t_block_info) {10, 10, 0xFFFFFF};
    }
}

static void fdf_init_z_size(t_fdf *fdf, int input_count, char *input_value[])
{
    int z_size;
    int i;

    if (input_count == 4)
    {
        if (!ft_str_is_integer(input_value[3], &z_size) || z_size <= 0)
            exit_with_error(EINVAL,"\tinvalid z_size");
        i = 0;
        while (input_value[3][i])
            if (input_value[3][i++] == ',')
                exit_with_error(EINVAL,"\tinvalid z_size format");
        fdf->map.z_scale = z_size;
    }
    else
        fdf->map.z_scale = 1;  
}

void    fdf_parser(t_fdf *fdf, int input_count, char *input_value[])
{
    int fd;

    if (!(input_count >= 2 && input_count <= 4 && fdf_input_is_valid_file_name(input_value[1])))
        exit_with_error(EINVAL, "\ttoo many arguments or invalid extensions");
    fd = open(input_value[1],O_RDONLY);
    if (fd < 0)
        exit_with_error(ENOENT, "\t error openning file");
	fdf_map_parser(fdf, fd);
	close(fd);
    fdf_init_block_info(fdf, input_count, input_value);
    fdf_init_z_size(fdf, input_count, input_value);
}