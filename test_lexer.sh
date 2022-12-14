# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_lexer.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/12 14:52:27 by t.fuji            #+#    #+#              #
#    Updated: 2022/12/19 15:54:53 by t.fuji           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# make cmd: make test_lexer_gettoken
# gcc -o minishell -g -l readline -I include -I libft/include libft/libft.a src/ms_lexer.c src/test_parser.c src/ms_lexer_gettoken.c src/ms_lexer_string.c src/ms_lexer_string_env.c src/ms_lexer_string_lst.c src/ms_lexer_tokenlen.c src/ms_parser.c src/ms_parser_cmdnew.c src/ms_parser_cmdnew_arg.c src/ms_parser_cmdnew_input.c src/ms_parser_cmdnew_output.c src/ms_parser_cmdnew_fdsize.c src/ms_getpath.c src/ms_utils.c 

echo	OK  	string
./minishell ""
./minishell " "
./minishell "   "
./minishell "oneString"
./minishell "Two Strings"
./minishell "3 plain strings"
./minishell " between spaces "
./minishell "  multiple  spaces  "
./minishell "arg is period ."
./minishell '_'
./minishell '\\'
./minishell '&'
./minishell '..'
./minishell '...'
./minishell '/'

echo	 NG  string
./minishell '.'

touch infile1 infile2 infile3

echo	 OK  	redirect and pipe
./minishell "cmd | cmd"
./minishell "cmd < infile1"
./minishell "cmd < infile1 < infile2 < infile3"
./minishell "cmd << EOF"
./minishell "cmd << ."
./minishell "cmd > outfile"
./minishell "cmd > outfile1 > outfile2 > outfile3"
./minishell "cmd >> appendfile"
./minishell "noSpace<infile1<infile2"
./minishell "noSpace<<EOF"
./minishell "noSpace>outfile1>outfile2"
./minishell "noSpace>>appendfile"
./minishell "pipe |> redirect"

echo	 NG  	redirect and pipe
./minishell "cmd || double pipes"
./minishell "cmd ||| triple pipes"
./minishell "cmd <> mixedRedirect"
./minishell "cmd >>> triple <<< redirect"

echo	 Not  	redirect and pipe
./minishell "colon: : semicolon; ;"

echo	 OK  	quote
./minishell '"Double quoted"'
./minishell "'Single quoted'"
./minishell "'Single quoted'\"Double quoted\""
./minishell "'Single quoted \"Double quote'"
./minishell "\"Double quoted 'Single quote\""
./minishell "'\"Double quoted\" in Single quoted'"
./minishell "\"'Single quoted'in Double quoted\""
./minishell "'in Single quoted \"Double quoted\"'"
./minishell "\"in Double quoted 'Single quoted'\""
./minishell "M'u'\"l\"t'i\"p\"l'e\" 'q'u\"o''t\"\"e\"'\"d'\"'"

echo	 Not  	special character
./minishell '\'
./minishell '`'
./minishell '`` back quotes'
./minishell '`back quoted`'

echo	 OK  	expansion
./minishell '$HOME'
./minishell 'Long_EnvVar $PATH'
./minishell 'NoExistsEnvVar $HOGE'
./minishell 'EnvVars_w/_NoSpaces $SHELL$HOME'
./minishell 'EnvVars_w/_Alpha $SHELLHOGE'
./minishell 'EnvVars_w/_Num $SHELL99'
./minishell 'DoubleQuotedEnvVar "$HOME"HOGE'
./minishell 'echo "$HOME"'
./minishell 'Status code $?'
./minishell 'Status code$?HOGE'

echo	 No  	expansion
./minishell "SingleQuotedEnvVar '\$HOME'"
./minishell 'Orphan $ dollar'
./minishell 'Double $$ dollars'
./minishell 'Parameter $1'
./minishell 'Parameter $1HOGE'
./minishell '$_ $_HOGE'

echo	 Edge	expansion
export VAR_SPACE=" "

echo	 OK  	multi pipes
./minishell "cmd1 | cmd2 | cmd3"
./minishell "cmd1 arg1 | cmd2 arg2 | cmd3 arg3"
./minishell "cmd1|cmd2|cmd3|cmd4"
./minishell "cmd1 arg1a arg1b|cmd2 arg2a arg2b|cmd3 arg3a arg3b|cmd4 arg4a arg4b"

echo  	NG  	multi pipes
./minishell '|'
./minishell 'end is pipe |'
./minishell '| begin is pipe'

echo	 OK  	combination
./minishell 'cmd1 < infile1| cmd2 arg1 | cmd3 > outfile1'
./minishell 'cmd1 < infile1| cmd2 arg1 arg2 | cmd3 >> outfile1'
./minishell 'cmd1 << EOF | cmd2 arg1 arg2 | cmd3 >> outfile1'
# ./minishell "echo \"\$HOME\" | ls | echo '\"in single quote str\"' | echo \"'\$HOME'\" > \"a.txt\" >>> error.txt <<< error.txt << correct_heredoc < infile1"
