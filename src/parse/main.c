/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:22:35 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/08 22:37:40 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int main(int argc, char **argv, char **env)
{
	// char	*str = "$USER -la | grep \"Ma$USER ke file\"da $HOME";
	// char	*str = "ls -la << EOF | awk \"<$HOME d\" | cat"; // << はヒアドキュメント（複数行を渡せる）
	// char	*str = "ls -l | cat << lim | cat > outfile | cat >> outfile";
	// char	*str = "ls -l | cat << lim | cat | cat";ret
	// char	*str = "ls | cat | cat | cat | > file | cat | cat | cat >> outfile";
	char	*str = "$USER -la | gre p \'Ma ke file\' $HOME";  // 「\'」 これで１文字とカウントされる
	char	**res;
	int		i;

	(void)argc;
	(void)argv;
	str = ft_correct_str(str);
	int i2 = 0;
	while (i2 < 38)
	{
		printf("after correct %d: %c\n", i2, str[i2]);
		i2++;
	}
	i = 0;
	res = ft_split_str(str, ' ');
	input_daller(res, env);
	// res = ft_correct_special(res, "<>|&");
	while (i < 38)
	{
		printf("%s\n", res[i]);
		free(res[i]);
		i++;
	}
	free(res);
	return (0);
}
