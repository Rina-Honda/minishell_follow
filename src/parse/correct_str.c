/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:53:35 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/15 16:43:35 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_correct_str_len(char *str, char *mark)
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

int	ft_handle_quotes(char *res, char *str, int *i, int extra)
{
	char	quote;

	quote = str[*i]; // copy start quote
	res[*i + extra] = str[*i];
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == quote)
			break ;
		res[*i + extra] = str[*i];
		(*i)++;
	}
	return (*i); // finish quoteのインデックス
}

void	ft_insert_spaces_around_makers(char *res, char *str, int i, int *extra)
{
	res[i + *extra] = ' ';
	res[i + *extra + 1] = str[i];
	res[i + *extra + 2] = ' ';
	*extra += 2;
}

void	ft_fill_correct_string(char *res, char *str, char *mark)
{
	int	i;
	int	extra;

	i = 0;
	extra = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			i = ft_handle_quotes(res, str, &i, extra);
		if (strchr(mark, str[i]))
			ft_insert_spaces_around_makers(res, str, i, &extra);
		else
			res[i + extra] = str[i];
		i++;
	}
	res[i + extra] = '\0';
}

char	*ft_correct_str(char *str)
{
	char	*res;
	int		new_len;

	new_len = ft_correct_str_len(str, "<>|");
	res = malloc(sizeof(char) * (new_len + 1));
	if (!res)
		return (NULL);
	ft_fill_correct_string(res, str, "<>|"); //quote内部のみretに格納
	return (res);
}
