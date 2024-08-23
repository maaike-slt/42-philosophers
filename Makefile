# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msloot <msloot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 19:19:04 by msloot            #+#    #+#              #
#    Updated: 2024/08/23 19:43:01 by msloot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philo
CC = 	cc
RM = 	rm -rf

CFLAGS =	-Wall -Werror -Wextra
CFLAGS +=	-pthread
CFLAGS +=	-g
# CFLAGS +=	-fsanitize=address

# **************************************************************************** #
#	MAKEFILE	#

MAKEFLAGS += --silent

SHELL := bash

B =		$(shell tput bold)
BLA =	$(shell tput setaf 0)
RED =	$(shell tput setaf 1)
GRE =	$(shell tput setaf 2)
YEL =	$(shell tput setaf 3)
BLU =	$(shell tput setaf 4)
MAG =	$(shell tput setaf 5)
CYA =	$(shell tput setaf 6)
WHI =	$(shell tput setaf 7)
D =		$(shell tput sgr0)
BEL =	$(shell tput bel)
CLR =	$(shell tput el 1)

# **************************************************************************** #
#	SOURCE	#

SRC_PATH =	./src/
OBJ_PATH =	./obj/
INC =		./inc/

SRC_NAME =	main.c thread.c parse.c running_philo.c \
			utils/ft_puterr.c utils/ft_strlen.c utils/ft_aton.c \
			utils/ft_isspace.c utils/ft_isdigit.c utils/ft_putstr_fd.c \
			utils/get_current_time.c utils/ft_putnbr_fd.c \

# SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

# *************************************************************************** #

define	progress_bar
	i=0
	while [[ $$i -le $(words $(SRC_NAME) m m) ]] ; do \
		printf " " ; \
		((i = i + 1)) ; \
	done
	printf "$(B)]\r[$(GRE)"
endef

# *************************************************************************** #
#	RULES	#

all:		launch $(NAME)

launch:
	$(call progress_bar)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@printf "\n$(B)$(MAG)$(NAME) compiled$(D)\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@) # 2> /dev/null || true
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@
	@printf "█"

clean:
	@$(RM) $(OBJ_PATH)
	@echo "$(B)cleared$(D)"

fclean:		clean
	@$(RM) $(NAME)
	@$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
