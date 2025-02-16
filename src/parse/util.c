/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:20:11 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/16 13:17:10 by rhonda           ###   ########.fr       */
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
			if (ft_strchr(act, s[j][i])) //わからん？→パイプとリダイレクト前後を切り離している
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
	cnt += j; //? j - 1じゃなくていい？→NULL分かも
	return (cnt);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = 0;
	while (s[len] && len < n)
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*ptr;
	int		i;

	i = 0;
	if (*dest != '\0')
		ptr = dest + ft_strlen(dest);
	else
	 	ptr = dest;
	while (src[i])
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return (dest);
}
