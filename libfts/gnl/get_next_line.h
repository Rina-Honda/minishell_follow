/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:45:56 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/05 21:53:29 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

//includes
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

//defines
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# if BUFFER_SIZE > INT_MAX
#  undef BUFFER_SIZE
#  define BUFFER_SIZE INT_MAX
# endif

# if BUFFER_SIZE < 1
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define EOF 26

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

typedef struct s_line
{
	char	*string;
	size_t	length;
	size_t	capacity;
}	t_line;

typedef struct s_buffinfo
{
	char	buff[BUFFER_SIZE];
	char	*buffptr;
	int		read_byte;
}	t_buffinfo;

//prototype declaration
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *str, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
#endif
