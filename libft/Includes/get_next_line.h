/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 07:17:58 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/18 12:21:32 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*ft_strjoin_gnl(char *str, char *line);
char	*ft_strdup_gnl(char *str);
int		ft_strlen_gnl(char *str);
char	*ft_strchr_gnl(char *str, char c);

char	*get_next_line(int fd);
char	*cut_line(char *line);
char	*first_line(int fd, char *str, char *line);

#endif