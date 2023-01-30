/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 01:12:23 by bamrouch          #+#    #+#             */
/*   Updated: 2023/01/19 17:43:33 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin_buffer_to_line(char **line, char *buffer)
{
	size_t	total_len;
	size_t	line_len;
	char	*res;

	if (!line || !(*line) || !buffer)
		return (NULL);
	line_len = ft_gnl_strlen(*line) + 1;
	total_len = line_len + ft_gnl_strlen(buffer);
	res = (char *)ft_calloc(total_len, sizeof(char));
	if (!res)
	{
		free((*line));
		return (NULL);
	}
	ft_gnl_strlcat(res, *line, line_len);
	free((*line));
	ft_gnl_strlcat(res, buffer, total_len);
	return (res);
}

char	*ft_cut_line(char *line, ssize_t len)
{
	char	*res;
	ssize_t	i;

	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
	{
		free(line);
		return (NULL);
	}
	ft_gnl_strlcat(res, line, len + 1);
	i = 0;
	while (line[len + i])
	{
		line[i] = line[len + i];
		i++;
	}
	line[i] = 0;
	return (res);
}

char	*get_next_line_helper(int fd, char *buffer, char **line)
{
	ssize_t	bytes_read;
	ssize_t	nl_index;
	ssize_t	i;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read >= 0 || (*line && bytes_read >= 0))
	{
		i = 0;
		*line = ft_strjoin_buffer_to_line(line, buffer);
		if (!(*line))
			return (NULL);
		while (buffer[i])
			buffer[i++] = 0;
		nl_index = ft_strchr_index(*line, '\n');
		if (nl_index >= 0)
			return (ft_cut_line(*line, nl_index + 1));
		else if (bytes_read < BUFFER_SIZE)
			return (ft_strjoin_buffer_to_line(line, ""));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		free(*line);
	if (bytes_read < 0)
		*line = NULL;
	return (NULL);
}

void	ft_init_vars(char **line, char **buffer)
{
	if (!(*line))
		*line = ft_calloc(1, sizeof(char));
	if (!(*line))
		return ;
	*buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!(*buffer))
	{
		free(*line);
		*line = NULL;
		return ;
	}
}

char	*get_next_line(int fd)
{
	static char	*line[10241];
	char		*buffer;
	char		*res;

	if (fd < 0 || fd > 10240 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_init_vars(&line[fd], &buffer);
	if (!line[fd] || !buffer)
		return (NULL);
	res = get_next_line_helper(fd, buffer, &line[fd]);
	free(buffer);
	if (ft_strchr_index(res, '\n') == -1)
		line[fd] = NULL;
	if (!res || ft_gnl_strlen(res) == 0)
	{
		if (res)
			free(res);
		return (NULL);
	}
	return (res);
}
