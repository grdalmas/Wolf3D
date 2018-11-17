# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    coverage.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: banthony <banthony@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/10 19:02:24 by banthony          #+#    #+#              #
#    Updated: 2018/09/10 19:04:02 by banthony         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	Compiler avec -fprofile-arcs -ftest-coverage
#	Lancer l'executable, tester toute les feature du programme
#	Ensuite run ce script, pour voir le pourcentage de code utilise

~/.brew/bin/lcov -c -d .. -o cov.data
~/.brew/bin/genhtml cov.data -o html
open html/index.html