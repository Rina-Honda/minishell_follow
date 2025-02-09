/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daller.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:55:30 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/09 20:28:11 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

size_t	ft_strlen_var(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	return (i);
}

char	*get_env_value(char *env)
{
	while (*env && *env != '=')
		env++;
	if (*env == '=')
		env++; //? ないことある？
	return (env);
}

int	calcu_new_str_len(char *env, char *str, int index)
{
	int		env_value_len;
	int		after_dollar_len;
	char	*env_value;

	env_value_len = 0;
	after_dollar_len = 0;
	env_value = get_env_value(env);
	while (env_value[env_value_len])
		env_value_len++;
	while (str[index + 1 + ft_strlen_var(&str[index + 1]) + after_dollar_len])
		after_dollar_len++;
	return (index + env_value_len + after_dollar_len + 1);
}

char	*replace_env_variable(char *env, char *str, int index)
{
	int		i;
	char	*ret;
	int		new_str_len;

	i = 0;
	new_str_len = calcu_new_str_len(env, str, index);
	ret = (char *)malloc(new_str_len); //? +1いらん？→calcuで対応済み
	if (!ret)
		return (NULL);
	// $以前
	while (i < index)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	// $環境変数の値
	ft_strlcat(ret, get_env_value(env), new_str_len + index + 2); //dstlenがnew_tr_len + index + 2なのはなんで？new_str_lenにindexも含まれてない？？
	// $環境変数より後
	ft_strlcat(ret, &str[index + 1 + ft_strlen_var(&str[index + 1])], new_str_len + index + 2);
	return (ret);
}

static char	*ft_expand_daller(char **env, char *str, int index)
{
	int		i;
	char	*ret;

	i = 0;
	while (env[i])
	{
		// 該当する環境変数が見つかったら入る
		if (!ft_strncmp(env[i], &str[index + 1], ft_strlen_var(&str[index + 1]) - 1) //?この後getenvになる？
			&& env[i][ft_strlen_var(&str[index + 1])] == '=') //?envが "  =  "じゃないときあるの？
		{
			ret = replace_env_variable(env[i], str, index);
			free(str); //? NULLチェックいらない？
			return (ret);
		}
		i++;
	}
	return (NULL); //なかったらNULLを返却
}

void	ft_check_var(char **str, char **env) // 「$」を変換(「\'」の内部は$を解釈しないためパスする、「\"」は解釈するためそのまま)
{
	int	i;

	while (*str)
	{
		i = 0;
		while (*str && (*str)[i])
		{
			if ((*str)[i] == '\'')
			{
				i++;
				while ((*str)[i] != '\'' && (*str)[i])
					i++;
			}
			else if ((*str)[i] == '$')
				*str = ft_expand_daller(env, *str, i);
			i++;
		}
		str++;
	}
}

// void	input_daller(char **str, char **env)
// {
// 	while (*str)
// 	{
// 		if (*str[0] == '$')
// 			*str = expand_daller(*str, env);
// 		str++;
// 	}
// }
