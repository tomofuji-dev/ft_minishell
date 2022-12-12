# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_lexer.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/12 14:52:27 by t.fuji            #+#    #+#              #
#    Updated: 2022/12/12 14:53:56 by t.fuji           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

./minishell "echo \"$HOME\""

# conbination
./minishell "echo \"$HOME\" | ls | echo \'\"in single quote str\"\' | echo \"\'$ZENO_PID'\" > \"a.txt\" >>> error.txt <<< error.txt << correct_heredoc < correct_input"