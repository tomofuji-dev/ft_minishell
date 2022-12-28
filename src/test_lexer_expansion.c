/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer_expansion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:32:17 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/29 00:57:18 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*expanded_str;
	const char	input1[] = "echo \'";
	const char	input2[] = "\"in \'doubleq\'\" \'in \"singleq\"\' $HOME 1";

	expanded_str = ms_lexer_string((char *)input);
	printf("%s\n%s\n", input, expanded_str);
}
