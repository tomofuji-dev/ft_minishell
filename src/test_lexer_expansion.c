/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer_expansion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:32:17 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/12 10:47:05 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*expanded_str;
	const char	input[] = "\"in \'doubleq\'\" \'in \"singleq\"\' $HOME ";

	expanded_str = ms_lexer_string((char *)input);
	printf("%s\n%s\n", input, expanded_str);
}
