/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:55:30 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/16 13:07:13 by rhonda           ###   ########.fr       */
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

static char	*get_env_value(char **env, const char *key)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=') //? env[i][key_len] != '='のときってどんな時？NULLとか？
			return (ft_strdup(env[i] + key_len + 1)); // valueの先頭ポインタ
		i++;
	}
	return (ft_strdup("")); //なかったら空文字列を返す
}

// int	calcu_new_str_len(char *env, char *str, int index)
// {
// 	int		env_value_len;
// 	int		after_dollar_len;
// 	char	*env_value;

// 	env_value_len = 0;
// 	after_dollar_len = 0;
// 	env_value = get_env_value(env);
// 	while (env_value[env_value_len])
// 		env_value_len++;
// 	while (str[index + 1 + ft_strlen_var(&str[index + 1]) + after_dollar_len])
// 		after_dollar_len++;
// 	return (index + env_value_len + after_dollar_len + 1);
// }

// char	*replace_env_variable(char *env, char *str, int index)
// {
// 	int		i;
// 	char	*ret;
// 	int		new_str_len;

// 	i = 0;
// 	new_str_len = calcu_new_str_len(env, str, index);
// 	ret = (char *)malloc(new_str_len); //? +1いらん？→calcuで対応済み
// 	if (!ret)
// 		return (NULL);
// 	// $以前
// 	while (i < index)
// 	{
// 		ret[i] = str[i];
// 		i++;
// 	}
// 	ret[i] = '\0';
// 	// $環境変数の値
// 	ft_strlcat(ret, get_env_value(env), new_str_len + index + 2); //dstlenがnew_tr_len + index + 2なのはなんで？new_str_lenにindexも含まれてない？？
// 	// $環境変数より後
// 	ft_strlcat(ret, &str[index + 1 + ft_strlen_var(&str[index + 1])], new_str_len + index + 2);
// 	return (ret);
// }

char	*ft_expand_daller(char **env, char *str)
{
	char	*new_str;
	char	quote;
	int		var_start;
	char	*var_name;
	char	*var_value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote = '\0';
	new_str = malloc(ft_strlen(str) * 2); //? 取り敢えずのバッファとして2倍？
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		printf("[DEBUG] i: %d, str[i] %c, quote: %c\n", i, str[i], quote ? quote : '-');
		// handle quote flag
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (quote == '\0')
				quote = str[i]; // copy start quote
			else if (quote == str[i])
				quote = '\0'; // end quoteのためフラグを戻す
			new_str[j++] = str[i++];
		}
		// handle $
		else if (str[i] == '$' && quote != '\'' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_')) //? alnumと_は環境変数構成要素の定義かな？
		{
			var_start = ++i; // $分進める
			while (ft_isalnum(str[i]) || str[i] == '_')
				i++;
			var_name = ft_strndup(&str[var_start], i - var_start);
			var_value = get_env_value(env, var_name);
			free(var_name);
			strcpy(&new_str[j], var_value);
			j += ft_strlen(var_value);
			free(var_value);
		}
		// 何もなければそのままコピー
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

// void	ft_check_var(char **str, char **env) // 「$」を変換(「\'」の内部は$を解釈しないためパスする、「\"」は解釈するためそのまま)
// {
// 	int	i;

// 	while (*str)
// 	{
// 		i = 0;
// 		while (*str && (*str)[i])
// 		{
// 			if ((*str)[i] == '\'')
// 			{
// 				i++;
// 				while ((*str)[i] != '\'' && (*str)[i])
// 					i++;
// 			}
// 			else if ((*str)[i] == '$')
// 				*str = ft_expand_daller(env, *str, i);
// 			i++;
// 		}
// 		str++;
// 	}
// }

char	*ft_handle_quotes(char *str) // シングルは$無視、ダブルは$を展開
{
	char	*new_str;
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote = '\0';
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1)); //? バッファいらん？
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		printf("[DEBUG] i: %d, str[i] %c, quote: %c\n", i, str[i], quote ? quote : '-');
		// handle quote
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (quote == '\0')
				quote = str[i]; // copy start quote
			else if (quote == str[i])
				quote = '\0'; // end quoteのためフラグを戻す
			i++; //? quoteをnew_strにいれないの？
		}
		// none quote
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*ft_join_tokens(char **tokens)
{
	int		len;
	char	*joined;

	if (!tokens || !tokens[0])
		return (NULL);
	len = 0;
	for (int i = 0; tokens[i]; i++)
		len += ft_strlen(tokens[i]) + 1; // +1 は区切り文字分
	joined = malloc(sizeof(char) * (len + 1));
	if (!joined)
		return (NULL);
	joined[0] = '\0';
	for (int i = 0; tokens[i]; i++)
	{
		ft_strcat(joined, tokens[i]);
		if (tokens[i + 1])
			ft_strcat(joined, " ");
	}
	return (joined);
}

void	input_daller(char **str, char **env)
{
	char	*expanded;
	char	*cleaned;
	char	*final_str;

	if (!str || !(*str))
		return ;
	// 環境変数
	printf("[DEBUG] Before Expansion: %s\n", *str);
	expanded = ft_expand_daller(env, *str);
	printf("[DEBUG] After Expansion: %s\n", expanded);
	// 引用符
	cleaned = ft_handle_quotes(expanded);
	printf("[DEBUG] After Quotes Handling: %s\n", cleaned);
	free(expanded);
	// 特殊文字
	char	**tokens = ft_split_str(cleaned, ' ');
	tokens = ft_correct_special(tokens, "<>|");
	// tokens再構築
	final_str = ft_join_tokens(tokens);
	free(*str);
	*str = final_str;
	printf("[DEBUG] After Special Handling: %s\n", *str);
}
