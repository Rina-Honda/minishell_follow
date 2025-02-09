/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:53:35 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/09 15:08:23 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_correct_len(char *str, char *mark)
{
	unsigned int	i;
	int				extra_mark;

	i = 0;
	extra_mark = 0;
	while (str[i])
	{
		ft_mv_quote(str, &i); //quoteなら次のquoteまでとばす //?片側quoteだとどうなる？？
		if (ft_strchr(mark, str[i])) //quote以外の特殊記号かチェック
			extra_mark += 2; //? なんで２？→記号の前後にスペースを入れるため
		i++;
	}
	return (i + extra_mark);
}

void	ft_fix_correct_str(char **ret, char *str, int *i, int *extra)
{
	char	quote;

	if (str[*i] == '\"' || str[*i] == '\'')
	{
		quote = str[*i];
		(*ret)[(*i + *extra)] = str[*i];
		(*i)++;
		while (str[*i])
		{
			(*ret)[*i + *extra] = str[*i];
			if (str[*i] == quote)
				break ;
			(*i)++;
		}
		if (ft_strchr("<>|&", str[*i]))
		{
			(*ret)[*i + *extra] = ' ';
			(*ret)[*i + *extra + 1] = str[*i];
			(*ret)[*i + *extra + 2] = ' ';
			(*extra) += 2;
		}
		else
			(*ret)[*i + *extra] = str[*i];
	}
	else if (str[*i] != ' ')
		(*ret)[(*i + *extra)] = str[*i]; //debug tmp
	else if (str[*i] == ' ')
		(*ret)[*i + *extra] = ' ';
}

char	*ft_correct_str(char *str)
{
	char	*ret;
	int		i;
	int		extra;

	i = 0;
	extra = 0;
	ret = malloc(sizeof(char) * (ft_correct_len(str, "<>|&") + 1));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		ft_fix_correct_str(&ret, str, &i, &extra); //quote内部のみretに格納
		i++;
	}
	ret[i + extra] = '\0';
	return (ret);
}
