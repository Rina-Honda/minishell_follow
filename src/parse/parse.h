/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:22:47 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/08 20:04:02 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <string.h>

# include "../../libfts/libft.h"

// prottype
int		main(int argc, char **argv, char **env);
char	*ft_correct_str(char *str);
char	**ft_split_str(char const *str, char c);
void	input_daller(char **str, char **env);
void	ft_mv_quote(char const *str, unsigned int *i);

#endif