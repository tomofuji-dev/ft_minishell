/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_gettoken.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:47:24 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/31 16:02:39 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ms_lexer_gettoken(t_token *token, char *line);
static int	ms_lexer_gettoken_classify(char *line);

void	ms_lexer_gettoken(t_token *token, char *line)
{
	char	*str;
	size_t	pos;
	size_t	len;
	size_t	i;

	pos = 0;
	i = 0;
	while (*(line + pos) != '\0')
	{
		while (*(line + pos) == CHRS_DELIM[0])
			pos++;
		len = ms_lexer_tokenlen(line + pos);
		str = ft_substr(line, pos, len);
		if (str == NULL)
			exit(ENOMEM);
		token[i].flag = ms_lexer_gettoken_classify(str);
		token[i].str = ms_lexer_string(str);
		free(str);
		pos += len;
		if (token[i].str != NULL)
			i++;
	}
	token[i].str = NULL;
	return ;
}

static int	ms_lexer_gettoken_classify(char *line)
{
	int		flag;

	if (line == NULL)
		return (FLAG_NONE);
	if (!ft_strchr(CHRS_DELIM, *line))
		return (FLAG_STRING);
	flag = FLAG_NONE;
	if (*line == CHRS_DELIM[1])
		flag = FLAG_IN;
	else if (*line == CHRS_DELIM[2])
		flag = FLAG_OUT;
	else if (*line == CHRS_DELIM[3])
		flag = FLAG_PIPE;
	if (*(line + 1) == '\0')
		return (flag);
	else if (*line == *(line + 1))
		flag += flag >> SHIFT_FLAG;
	if (*(line + 2) == '\0' && *(line + 1) != CHRS_DELIM[3])
		return (flag);
	return (FLAG_NONE);
}
