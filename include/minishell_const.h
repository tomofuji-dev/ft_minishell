/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_const.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:51:23 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/31 17:13:28 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_CONST_H
# define MINISHELL_CONST_H

# define CHR_DIR			'/'
# define CHR_HOME			'~'
# define CHR_SPACE			' '
# define CHR_NL				'\n'
# define CHR_SEP			':'
# define CHR_EQUAL			'='
# define CHR_SNAKE			'_'
# define CHR_STATUS			'?'

# define INVALID_FILENO		-1
# define ERR_NOERR			0
# define STATUS_SUCCESS		0
# define STATUS_FAILURE		1
# define STATUS_NOT_EXEC	126
# define STATUS_NO_CMD		127
# define STATUS_BASE		128
# define STATUS_MASK		0xff

# define SIZE_INVALID		-1

# define FLAG_NONE			0x00
# define FLAG_STRING		0x10
# define FLAG_IN			0x20
# define FLAG_HEREDOC		0x22
# define FLAG_OUT			0x40
# define FLAG_APPEND		0x44
# define FLAG_PIPE			0x80
# define SHIFT_FLAG			4

# define LEN_QUOTE_CLOSED	2
# define LEN_QUOTE_UNCLOSED	1

#endif
