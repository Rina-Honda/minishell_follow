/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:57:46 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/08 19:59:52 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	ft_wordlen(char const *str, char c)
{
	unsigned int	i;
	int				len; //?なんでunsignedじゃない？マイナスになる？

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != c) // not space
		{
			len++;
			while (str[i] && str[i] != c)
				i++;
		}
		else // space
			i++;
	}
	return (len);
}

static char	*ft_allocate_word(char const *str, char c)
{
	int		len;
	char	*word;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	word = strndup(str, len); //?アレンジ
	word[len] = '\0';
	return (word);
}

static void	ft_free_array(char **array, int i)
{
	while (i > 0)
		free(array[--i]);
	free(array);
}

char	**ft_split_str(char const *str, char c)
{
	char	**array;
	int		words;
	int		i;

	words = ft_wordlen(str, c);
	array = malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (*str != c) // not space
		{
			array[i] = ft_allocate_word(str, c);
			if (!array[i])
				return (ft_free_array(array, i), NULL);
			while (*str && *str != c)
				str++;
			i++;
		}
		else // space
			str++;
	}
	array[i] = NULL;
	return (array);
}
