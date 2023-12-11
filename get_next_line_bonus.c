/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmafrid <asmafrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:04:30 by asmafrid          #+#    #+#             */
/*   Updated: 2023/12/11 15:04:31 by asmafrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(int fd, char *str)
{
	char	*buff;
	int		len;

	buff = malloc((size_t)(BUFFER_SIZE + 2) * sizeof(char));
	if (!buff)
		return (NULL);
	len = 1;
	while (!ft_strchr(str, '\n') && (len != 0))
	{
		len = read(fd, buff, BUFFER_SIZE);
		if (len == -1)
		{
			free(buff);
			free(str);
			return (NULL);
		}
		buff[len] = '\0';
		str = ft_strjoin_mod(str, buff);
	}
	free(buff);
	return (str);
}

char	*ft_line(char *str)
{
	int		i;
	char	*line_new;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line_new = (char *)malloc(sizeof(char) * (i + 2));
	if (!line_new)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line_new[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line_new[i] = str[i];
		i++;
	}
	line_new[i] = '\0';
	return (line_new);
}

char	*ft_skip(char *old_buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	while (old_buffer[i] != '\0' && old_buffer[i] != '\n')
		i++;
	if (old_buffer[i] == '\0')
	{
		free(old_buffer);
		return (NULL);
	}
	new_buffer = malloc(sizeof(char) * (ft_strlen(old_buffer) - i + 1));
	if (new_buffer == NULL)
		return (NULL);
	i++;
	j = 0;
	while (old_buffer[i] != '\0')
		new_buffer[j++] = old_buffer[i++];
	new_buffer[j] = '\0';
	free(old_buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	char		*line_temp;
	static char	*buffer[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	buffer[fd] = ft_read(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line_temp = ft_line(buffer[fd]);
	buffer[fd] = ft_skip(buffer[fd]);
	return (line_temp);
}
