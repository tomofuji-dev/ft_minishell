/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_string.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:51:23 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/10 16:32:00 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRING_H
# define MINISHELL_STRING_H

//# define CHRS_DELIM		" <>|;&()" for bonus+
# define CHRS_DELIM			" <>|"
# define CHRS_QUOTE			"$\"'"

# define STR_EMPTY			""
# define STR_DIR			"/"
# define STR_OLDPWD			"-"
# define STR_QUOTE			"'"
# define STR_DQUOTE			"\""
# define STR_EXPAND			"$"

# define CMD_CD				"cd"
# define CMD_ECHO			"echo"
# define CMD_ENV			"env"
# define CMD_EXIT			"exit"
# define CMD_EXPORT			"export"
# define CMD_PWD			"pwd"
# define CMD_UNSET			"unset"

# define OPTION_NONL		"-n"

# define ENV_HOME			"HOME"
# define ENV_PATH			"PATH"
# define ENV_PWD			"PWD"
# define ENV_OLDPWD			"OLDPWD"

# define MSG_SIG_QUIT		"Quit: 3"
# define MSG_SYNTAX_ERR		"syntax error"
# define MSG_EXIT			"exit"
# define MSG_NO_HOME		"HOME not set"
# define MSG_NO_OLDPWD		"OLDPWD not set"
# define MSG_ENOENT			"No such file or directory"
# define MSG_ARG_NOTNUM		"numeric argument required"
# define MSG_ARG_MANY		"too many arguments"
# define MSG_DECLARE		"declare -x "
# define MSG_INVAL_ID		"bash: %s: `%s\" : not a valid identifier\n"
# define MSG_NO_CMD			"command not found"
# define MSG_ISDIR			"Is a directory"

# define PROMPT_MINISH		"minishell $ "
# define PROMPT_HREDOC		"> "

#endif
