/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:28:00 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/13 15:27:18 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ms_parser(t_token* token)
{
	while (token)
	{
		if (token == PIPE && cmd == NULL)
			return NULL;
		if (token == PIPE)
			token = token->next;
		t_cmd *new_cmd = create_token(&token);
		{
			// pipeまで or NULLまでのcmd arg, redirectを構造体のメンバ変数とする
				// accessでcmd pathを取得する
			// redirectがあったらfdを開いて保存
			// heredocがあったらfdを開いてbufferに書き込む
			// errorがあったらfreeした上でNULLを返す
			// tokenを読み進める
		}
		if (new_cmd == NULL)
			// NULLだったらこれまでのtoken, cmd全てをfreeしてerror処理
	}
}
