/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daller.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:55:30 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/08 19:56:28 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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

void	input_daller(char **str, char **env)
{
	while (*str)
	{
		if (*str[0] == '$')
			*str = expand_daller(*str, env);
		str++;
	}
}
