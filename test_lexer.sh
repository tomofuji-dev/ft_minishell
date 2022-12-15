# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_lexer.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/12 14:52:27 by t.fuji            #+#    #+#              #
#    Updated: 2022/12/15 14:56:57 by tfujiwar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# make cmd: make test_lexer_gettoken

./minishell "echo \"\$HOME\""

# string
./minishell ""
./minishell " "
./minishell "   "
./minishell "oneString"
./minishell "Two Strings"
./minishell "3 plain strings"
./minishell " between spaces "

# redirect and pipe
./minishell "cmd | cmd"
touch infile1 infile2 infile3
./minishell "cmd < infile1"
./minishell "cmd < infile1 < infile2 < infile3"
./minishell "cmd << EOF"
./minishell "cmd > outfile"
./minishell "cmd > outfile1 > outfile2 > outfile3"
./minishell "cmd >> appendfile"
./minishell "noSpace<infile"
./minishell "noSpace<<EOF"
./minishell "noSpace>outfile"
./minishell "noSpace>>appendfile"
./minishell "pipe |> redirect"
./minishell "cmd || double pipes"
./minishell "cmd ||| triple pipes"
./minishell "cmd <> mixedRedirect"
./minishell "cmd >>> triple <<< redirect"
./minishell "colon: : semicolon; ;"

# quote
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

# expansion
./minishell '$HOME'
./minishell 'Long_EnvVar $PATH'
./minishell 'NoExistsEnvVar $HOGE'
./minishell 'EnvVars_w/_NoSpaces $SHELL$HOME'
./minishell 'EnvVars_w/_Alpha $SHELLHOGE'
./minishell 'EnvVars_w/_Num $SHELL99'
./minishell "SingleQuotedEnvVar '\$HOME'"
./minishell 'DoubleQuotedEnvVar "$HOME"HOGE'

# combination
# ./minishell "echo \"\$HOME\" | ls | echo '\"in single quote str\"' | echo \"'\$HOME'\" > \"a.txt\" >>> error.txt <<< error.txt << correct_heredoc < infile1"
