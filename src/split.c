/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:22:35 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/08 19:30:09 by rhonda           ###   ########.fr       */
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

char	*ft_strncpy(const char *src, size_t n)
{
	char	*dst;
	size_t	i;

	dst = (char *)malloc(sizeof(char) * (n + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
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

static char	*expand_daller(char *word, char **env)
{
	int		i;
	char	*ret;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], word + 1, ft_strlen(word) - 1)) //?この後getenvになる？
		{
			ret = ft_strdup(&env[i][5]); //?決め打ち？
			free(word); //?NULLチェックいらない？
			return (ret);
		}
		i++;
	}
	return (word); //なかったらもらった値をそのまま返却
}

static void	input_daller(char **str, char **env)
{
	while (*str)
	{
		if (*str[0] == '$')
			*str = expand_daller(*str, env);
		str++;
	}
}

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

int main(int argc, char **argv, char **env)
{
	// char	*str = "$USER -la | grep \"Ma$USER ke file\"da $HOME";
	// char	*str = "ls -la << EOF | awk \"<$HOME d\" | cat"; // << はヒアドキュメント（複数行を渡せる）
	// char	*str = "ls -l | cat << lim | cat > outfile | cat >> outfile";
	// char	*str = "ls -l | cat << lim | cat | cat";ret
	// char	*str = "ls | cat | cat | cat | > file | cat | cat | cat >> outfile";
	char	*str = "$USER -la | gre p \'Ma ke file\' $HOME"; // 「\'」 これで１文字とカウントされる
	char	**res;
	int		i;

	(void)argc;
	(void)argv;
	str = ft_correct_str(str);
	// int i2 = 0;
	// while (i2 < 38)
	// {
	// 	printf("after correct %d: %c\n", i2, str[i2]);
	// 	i2++;
	// }
	i = 0;
	res = ft_split_str(str, ' ');
	input_daller(res, env);
	// res = ft_correct_special(res, "<>|&");
	while (res[i])
	{
		printf("%s\n", res[i]);
		free(res[i]);
		i++;
	}
	free(res);
	return (0);
}
