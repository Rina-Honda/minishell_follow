/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:45:44 by rhonda            #+#    #+#             */
/*   Updated: 2024/07/21 22:57:47 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	ft_getchar(int fd)
{
	static t_buffinfo	buffinfo;
	char				c;

	if (buffinfo.read_byte == 0)
	{
		buffinfo.read_byte = read(fd, buffinfo.buff, BUFFER_SIZE);
		if (buffinfo.read_byte <= 0)
		{
			ft_memset(buffinfo.buff, 0, BUFFER_SIZE);
			buffinfo.read_byte = 0;
			return (EOF);
		}
		buffinfo.buffptr = buffinfo.buff;
	}
	buffinfo.read_byte--;
	c = *(buffinfo.buffptr++);
	return (c);
}

static char	*ft_appendchar(t_line *line, char c)
{
	char	*new_str;

	if (line->length + 1 >= line->capacity)
	{
		if (!line->capacity)
			line->capacity = 2;
		else
			line->capacity *= 2;
		new_str = (char *)malloc(sizeof(char) * line->capacity);
		if (!new_str)
			return (NULL);
		if (line->string)
		{
			ft_memcpy(new_str, line->string, line->length);
			free(line->string);
		}
		line->string = new_str;
	}
	line->string[line->length] = c;
	line->length++;
	line->string[line->length] = '\0';
	return (line->string);
}

char	*get_next_line(int fd)
{
	t_line	result;
	char	c;

	if (fd < 0 || OPEN_MAX <= fd)
		return (NULL);
	result.string = NULL;
	result.length = 0;
	result.capacity = 0;
	while (1)
	{
		c = ft_getchar(fd);
		if (c == EOF)
			break ;
		if (!ft_appendchar(&result, c))
		{
			free(result.string);
			return (NULL);
		}
		if (c == '\n')
			break ;
	}
	if (result.length > 0)
		return (result.string);
	free(result.string);
	return (NULL);
}

// #include <stdio.h>
// #include <fcntl.h>
// int main(void){
//     int fd = open("example.txt", O_RDONLY);
// 	char    *line;

//     if(fd < 0)
//         return -1;
//     while((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s", line);
//         free(line);
//     }
//     close(fd);

// 	// system("leaks a.out");
// 	return 0;
// }