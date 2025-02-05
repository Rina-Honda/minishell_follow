/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:09:06 by rhonda            #+#    #+#             */
/*   Updated: 2023/10/29 20:14:44 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// #include <stdio.h>

// int main(void)
// {
//     char character = '\0';
//     int file_descriptor = 1;

//     printf("Output using printf: %c\n", character);

//     ft_putchar_fd(character, file_descriptor);

//     return 0;
// }