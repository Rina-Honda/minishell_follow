/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:20:11 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/09 20:48:40 by rhonda           ###   ########.fr       */
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

int	ft_array_len(char **s, char *act)
{
	unsigned int	i;
	int				j;
	int				cnt;

	j = 0;
	cnt = 0;
	while (s && s[j])
	{
		i = 0;
		while (s[j][i])
		{
			ft_mv_quote(s[j], &i);
			if (ft_strchr(act, s[j][i])) //?わからん？
			{
				cnt++;
				if (i > 0)
					cnt++;
				if (s[j][i + 1])
					cnt++;
			}
			i++;
		}
		j++;
	}
	cnt += j;
	return (cnt);
}
