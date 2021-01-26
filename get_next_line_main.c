/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tapark <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:13:21 by tapark            #+#    #+#             */
/*   Updated: 2020/11/12 17:17:16 by tapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "get_next_line.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 6
# endif

# ifndef MAX
#  define MAX 32
# endif

int get_line_break(char *backup)
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

char	*ft_strdup(char *s1)
{
	char	*dest;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s1[len])
		len++;
	if (!(dest = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int ft_strlen(const char *s1)
{
	int len;

	len = 0;
	while (s1[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*str;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = 0;
	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
		return (!(s1) ? ft_strdup(s2) : ft_strdup(s1));
	if (!(str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (NULL);
	s1_len = 0;
	s2_len = 0;
	while (s1[s1_len])
		str[i++] = s1[s1_len++];
	free(s1);
	while (s2[s2_len])
		str[i++] = s2[s2_len++];
	str[i] = '\0';
	return (str);
}

int	get_next_line(int fd, char **line)
{
	char buf[BUFFER_SIZE + 1];
	int RS;
	static char *backup[MAX];
	int LB;
	char *temp;
	int len;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	while ((RS = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[RS] = '\0';
		if (backup[fd] == 0)
			backup[fd] = ft_strdup(buf);
		else
			backup[fd] = ft_strjoin(backup[fd], buf);

	}
	if (RS < 0)
		return (-1);
	LB = get_line_break(backup[fd]);
	if (LB != -1 && backup[fd])
	{
		backup[fd][LB] = '\0';
		*line = ft_strdup(backup[fd]);
		if ((len = ft_strlen(backup[fd]) + LB + 1) == 0)
		{
			free(backup[fd]);
			backup[fd] = 0;
			return (1);
		}
		temp = ft_strdup(backup[fd] + LB + 1);
		free(backup[fd]);
		backup[fd] = temp;
		return (1);
	}
	else if (backup[fd])
	{
		*line = ft_strdup(backup[fd]);
		free(backup[fd]);
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int main(void)
{
    char *line = 0;
    int ret;
    int fd;;

    fd = open("user.txt", O_RDONLY);
    while ((ret = get_next_line(fd, &line)) > 0)
    {
        printf("%s\n", line);
        free(line);
    }
    printf("%s\n", line);
    free(line);
    return (0);
}
