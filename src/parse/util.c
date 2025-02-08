/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:20:11 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/08 20:20:18 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ft_mv_quote(char const *str, unsigned int *i)
{
	char	quote;

	if (str[*i] == '\"' || str[*i] == '\'')
	{
		quote = str[*i];
		(*i)++;
		while (str[*i])
		{
			if (str[*i] == quote)
				break ;
			(*i)++;
		}
	}
}
