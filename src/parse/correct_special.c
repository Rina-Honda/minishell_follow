/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 20:12:01 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/16 13:35:10 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	ft_correct_len(char **str, char *specials)
{
	int	len;

	len = 1;
	if (!*str)
		return (0);
	while (str[0] && str[1]) //? ヒアドキュとappend系out用かな？まだわからん
	{
		if (ft_strchr(specials, str[0][0]) && (str[0][0] == str[1][0])
			&& ft_strlen(str[0]) == 1 && ft_strlen(str[1]) == 1)
			str++;
		len++;
		str++;
	}
	return (len);
}

char	*ft_fill_wrd(char *str)
{
	char	*n_wrd;

	n_wrd = malloc(3); //? 決め打ち？
	if (!n_wrd)
		return (NULL);
	n_wrd[0] = str[0];
	n_wrd[1] = str[0];
	n_wrd[2] = '\0';
	return (n_wrd);
}

static char	**ft_correct_fill(char **res, char **str, char *specials)
{
	int		len;
	char	*n_wrd;

	len = 0;
	if (!*str)
		return (0);
	while (str[0] && str[1]) //? 決め打ち？
	{
		if (ft_strchr(specials, str[0][0]) && (str[0][0] == str[1][0])
			&& ft_strlen(str[0]) == 1 && ft_strlen(str[1]) == 1)
		{
			n_wrd = ft_fill_wrd(str[0]);
			free(str[0]);
			free(str[1]);
			res[len++] = n_wrd;
			str++;
		}
		else
			res[len++] = *str;
		str++;
	}
	if (str) //? 何してる？
		res[len++] = *str;
	res[len] = NULL;
	return (res);
}

char	**ft_correct_special(char **str, char *specials) // handle "<>|"
{
	int		n_len;
	char	**res;

	n_len = ft_correct_len(str, specials);
	res = malloc(sizeof(char *) * (n_len + 1));
	if (!res)
		return (NULL);
	res = ft_correct_fill(res, str, specials);
	if (!res)
		return (str);
	free(str);
	return (res);
}
