/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:57:46 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/15 22:32:50 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

// static int	ft_wordlen(char const *str, char c)
// {
// 	unsigned int	i;
// 	int				len; //?なんでunsignedじゃない？マイナスになる？

// 	i = 0;
// 	len = 0;
// 	while (str[i])
// 	{
// 		if (str[i] != c) // not space
// 		{
// 			len++;
// 			while (str[i] && str[i] != c)
// 				i++;
// 		}
// 		else // space
// 			i++;
// 	}
// 	return (len);
// }

// static char	*ft_allocate_word(char const *str, char c)
// {
// 	int		len;
// 	char	*word;

// 	len = 0;
// 	while (str[len] && str[len] != c)
// 		len++;
// 	word = malloc(sizeof(char) * (len + 1));
// 	if (!word)
// 		return (NULL);
// 	word = strndup(str, len); //?アレンジ
// 	word[len] = '\0';
// 	return (word);
// }

// static void	ft_free_array(char **array, int i)
// {
// 	while (i > 0)
// 		free(array[--i]);
// 	free(array);
// }

static int	ft_word_num(char const *s, char c)
{
	unsigned int	i;
	unsigned int	flag;
	int				num;

	i = 0;
	flag = 0;
	num = 0;
	while (s[i])
	{
		ft_mv_quote(s, &i);
		if (!flag && s[i] != c)
			flag = 1;
		else if (flag && s[i] == c)
		{
			num++;
			flag = 0;
		}
		i++;
	}
	if (flag)
		num++;
	return (num);
}

int	ft_char_len(char *s, char c)
{
	unsigned int	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		ft_mv_quote(s, &i);
		i++;
	}
	return (i);
}

char	*ft_fill_word(char *word, char *s, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int	ft_split_low(char **array, char const *s, char c)
{
	char	*str;
	char	*word;
	int		len;
	int		i;

	str = (char *)s;
	i = 0;
	while (i < ft_word_num(s, c)) //?strあるかチェックいらない？
	{
		len = ft_char_len(str, c);
		if (len > 0)
		{
			word = malloc(sizeof(char) * (len + 1));
			if (word == NULL)
			{
				ft_putstr_fd("Error: malloc failed in ft_split_low()\n", 2);
				return (i + 1);
			}
			word = ft_fill_word(word, str, len);
			array[i] = word;
			str += len + 1; //? +1どこからきた？→たぶん区切り文字分も進めてる
			i++;
		}
		else if (*str != '\0')
			str++;
	}
	array[ft_word_num(s, c)] = NULL;
	return (0);
}

char	**ft_split_str(char const *str, char c)
{
	char	**array;
	int		words;
	int		i;

	// printf("%d\n", ft_word_num(str, c));
	words = ft_word_num(str, c);
	array = malloc(sizeof(char *) * (words + 1));
	if (!array)
	{
		ft_putstr_fd("Error: malloc failed in ft_split_str()\n", 2);
		return (NULL);
	}
	i = 0;
	while (i < words) //init
	{
		array[i] = NULL;
		i++;
	}
	if (ft_split_low(array, str, c)) // 途中で失敗したら全free
	{
		i = 0;
		while (i < words)
		{
			free(array[i]);
			i++;
		}
		free(array);
		return (NULL);
	}
	printf("=== Debug Splited Tokens ===\n");
	for (int i = 0; array[i]; i++)
		printf("Token[%d]: %s (addr: %p)\n", i, array[i], (void *)array[i]);
	printf("============================\n");
	return (array);
}
