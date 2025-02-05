/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:37:24 by rhonda            #+#    #+#             */
/*   Updated: 2024/03/20 20:27:34 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

//header files
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

//prototype declarations
size_t	ft_strlen(const char *s);
int		ft_strchr(const char *s, int c);

int		ft_printf(const char *format, ...);
int		ft_print_c(va_list *ap);
int		ft_print_s(va_list *ap);
int		ft_print_p(va_list *ap);
int		ft_print_idux(va_list *ap, int specifier);
int		ft_print_percent(void);

#endif