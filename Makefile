# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/29 19:24:03 by ysarac            #+#    #+#              #
#    Updated: 2023/12/29 19:24:03 by ysarac           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAG = -Wall -Wextra -Werror -g

all:
	@echo Mandatory compiled
	@gcc $(FLAG) server.c -o server
	@gcc $(FLAG) client.c -o client
	@rm -rf server.dSYM
	@rm -rf client.dSYM
	@rm -rf server_bonus
	@rm -rf client_bonus
	
bonus:
	@echo Bonus compiled
	@gcc $(FLAG) server_bonus.c -o server_bonus
	@gcc $(FLAG) client_bonus.c -o client_bonus
	@rm -rf server_bonus.dSYM
	@rm -rf client_bonus.dSYM
	@rm -rf server
	@rm -rf client

run: all
	@./server
brun: bonus
	@./server_bonus
clean:
	@echo Cleaned
	@rm -rf server
	@rm -rf client
	@rm -rf server_bonus
	@rm -rf client_bonus

fclean: clean

re: fclean all

.PHONY : all bonus clean fclean	