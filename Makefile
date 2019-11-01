# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bjasper <bjasper@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/21 13:25:20 by bjasper           #+#    #+#              #
#    Updated: 2019/10/23 18:15:00 by bjasper          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all re clean fclean

NAME = fillit
SRCS = fillit.c 
LIBA_PATH = /Users/bjasper/fillit/libft
LIBA = libft.a

all: $(NAME)

$(NAME): $(LIBA)
	gcc -g -o $(NAME) $(SRCS) $(LIBA_PATH)/$(LIBA) 
	
$(LIBA):
	$(MAKE) -C $(LIBA_PATH)
	$(MAKE) clean -C $(LIBA_PATH)
	
clean:
	rm -rf $(NAME)
	
fclean: clean

re: fclean all
