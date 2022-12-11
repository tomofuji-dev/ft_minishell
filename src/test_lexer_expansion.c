/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer_expansion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:32:17 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/11 16:24:25 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main(void)
{
	char		*expanded_str;
	const char	input[] = "\"in \'doubleq\'\" \'in \"singleq\"\' $HOME ";

	init_global();

	expanded_str = ms_substr_and_expand(input);
	printf("%s\n%s\n", input, expanded_str);
}
