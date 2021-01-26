/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tapark <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:13:21 by tapark            #+#    #+#             */
/*   Updated: 2020/11/18 15:19:17 by tapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_line_break(char *backup)
{
	int n;

	if (backup == 0)
		return (-1);
	n = 0;
	while (backup[n])
	{
		if (backup[n] == '\n')
			return (n);
		n++;
	}
	return (-1);
}

int		get_break_line(char **backup, char **line, int line_break)
{
	char	*temp;
	int		len;

	(*backup)[line_break] = '\0';
	*line = ft_strdup(*backup);
	len = ft_strlen(*backup + line_break + 1);
	if (len == 0)
	{
		free(*backup);
		*backup = 0;
		return (1);
	}
	temp = ft_strdup(*backup + line_break + 1);
	free(*backup);
	*backup = temp;
	return (1);
}

int		get_end_line(char **backup, char **line)
{
	int line_break;

	line_break = get_line_break(*backup);
	if (*backup && line_break != -1)
		return (get_break_line(backup, line, line_break));
	else if (*backup)
	{
		*line = *backup;
		*backup = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int		get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	static char		*backup[MAX];
	int				line_break;
	int				read_size;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	while ((read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = '\0';
		if (backup[fd] == 0)
			backup[fd] = ft_strdup(buf);
		else
			backup[fd] = ft_strjoin(backup[fd], buf);
		if ((line_break = get_line_break(backup[fd])) != -1)
			return (get_break_line(&backup[fd], line, line_break));
	}
	if (read_size < 0)
		return (-1);
	return (get_end_line(&backup[fd], line));
}
