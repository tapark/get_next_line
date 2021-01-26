/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tapark <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 20:57:58 by tapark            #+#    #+#             */
/*   Updated: 2020/11/18 15:19:33 by tapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# ifndef MAX
#  define MAX 32
# endif

int		get_next_line(int fd, char **line);
char	*ft_strdup(char *s1);
int		ft_strlen(char *s1);
char	*ft_strjoin(char *s1, char *s2);

#endif
