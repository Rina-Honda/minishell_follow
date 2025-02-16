/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:22:47 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/16 12:26:16 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

// include
# include <string.h>
# include "../../libfts/libft.h"

// prottype
int		main(int argc, char **argv, char **env);
// char	*ft_correct_str(char *str);
char	**ft_correct_special(char **str, char *specials);
char	**ft_split_str(char const *str, char c);
// void	ft_check_var(char **str, char **env);
void	input_daller(char **str, char **env);

void	ft_mv_quote(char const *str, unsigned int *i);
int		ft_array_len(char **s, char *act);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strcat(char *dest, const char *src);

#endif
