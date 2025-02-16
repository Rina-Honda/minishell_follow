/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:22:35 by rhonda            #+#    #+#             */
/*   Updated: 2025/02/16 13:47:28 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	main(int argc, char **argv, char **env)
{
	char	*str1 = ft_strdup(">>$USER|grep \"<$HOME d\" >>file");
	// char	*str2 = ft_strdup("'$USER' \"$HOME\"");
	// char	*str3 = ft_strdup("echo \"$USER\" | grep 'home'");

	(void)argc;
	(void)argv;
	printf("=== Before Expansion ===\n");
	printf("str1: %s\n", str1);
	// printf("str2: %s\n", str2);
	// printf("str3: %s\n", str3);
	fflush(stdout);

	input_daller(&str1, env);
	// input_daller(&str2, env);
	// input_daller(&str3, env);

	printf("=== After Expansion ===\n");
	printf("str1: %s\n", str1);
	// printf("str2: %s\n", str2);
	// printf("str3: %s\n", str3);

	free(str1);
	// free(str2);
	// free(str3);
	return (0);
}

// int main(int argc, char **argv, char **env)
// {
// 	// int e = 0;
// 	// while (env[e])
// 	// {
// 	// 	printf("%s\n", env[e]);
// 	// 	e++;
// 	// }

// 	// char	*str = "$USER -la | grep \"Ma$USER ke file\"da $HOME";
// 	// char	*str = "ls -la << EOF | awk \"<$HOME d\" | cat"; // << はヒアドキュメント（複数行を渡せる）
// 	// char	*str = "ls -l | cat << lim | cat > outfile | cat >> outfile";
// 	// char	*str = "ls -l | cat << lim | cat | cat";ret
// 	// char	*str = "ls | cat | cat | cat | > file | cat | cat | cat >> outfile";
// 	char	*str = "USER|grep $HOME";
// 	// char	*str = "$USER -la | gre p \'Ma ke$HOME file\' $HOME";  // 「\'」 これで１文字とカウントされる
// 	char	**res;
// 	size_t		i;

// 	(void)argc;
// 	(void)argv;
// 	str = ft_correct_str(str);
// 	res = ft_split_str(str, ' ');
// 	ft_check_var(res, env);
// 	printf("%d\n", ft_array_len(res, "<|>"));
// 	i = 0;
// 	while (res[i] != NULL)
// 	{
// 		printf("%s\n", res[i]);
// 		free(res[i]);
// 		i++;
// 	}
// 	// printf("pipe etc\n");
// 	free(res);
// 	return (0);
// }
