/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_gettoken.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:47:24 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/15 17:25:02 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ms_lexer_gettoken(char *line, size_t size);
int		ms_lexer_gettoken_classify(char *line);

t_token	*ms_lexer_gettoken(char *line, size_t size)
{
	t_token	*token;
	size_t	pos;
	size_t	len;
	size_t	i;

	token = (t_token *)malloc((size + 1) * sizeof(t_token));
	if (token == NULL)
		exit(ENOMEM);
	pos = 0;
	i = 0;
	while (*(line + pos) != '\0')
	{
		while (*(line + pos) == CHRS_DELIM[0])
			pos++;
		len = ms_lexer_tokenlen(line + pos);
		token[i].str = ft_substr(line, pos, len);
		if (token[i].str == NULL)
			exit(ENOMEM);
		token[i].flag = ms_lexer_gettoken_classify(token[i].str);
		token[i].str = ms_lexer_string(token[i].str);
		pos += len;
		i++;
	}
	token[size].str = NULL;
	return (token);
}

int	ms_lexer_gettoken_classify(char *line)
{
	int		flag;

	if (line == NULL)
		return (0x00);
	if (!ft_strchr(CHRS_DELIM, *line))
		return (0x10);
	flag = 0;
	if (*line == CHRS_DELIM[1])
		flag = 0x20;
	else if (*line == CHRS_DELIM[2])
		flag = 0x40;
	else if (*line == CHRS_DELIM[3])
		flag = 0x80;
	if (*(line + 1) == '\0')
		return (flag);
	else if (*line == *(line + 1))
		flag += flag >> 4;
	if (*(line + 2) == '\0' && *(line + 1) != CHRS_DELIM[3])
		return (flag);
	return (0x00);
}
