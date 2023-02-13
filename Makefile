# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afindo <afindo@student.roma42.it>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/26 09:04:11 by afindo            #+#    #+#              #
#    Updated: 2023/02/12 20:34:13 by afindo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc
CC_FLAGS	= -Wall -Wextra -Werror
RM			= rm -rf
NORMINETTE	= norminette
HEADS 		= ./includes/
SRCS		= ./srcs/
SRC			= push_swap.c \
			  init_stacks.c \
			  stacks.c \
			  align_stacks.c \
			  operations.c \
			  instructions.c \
			  movements.c \
			  states.c \
			  resolution.c \
			  bruteforce.c \
			  bruteforce_operations.c \
			  utils.c \
			  cleaner.c \
			  print.c \
			  debug.c \
			  extra.c
OBJS 		= $(SRC:%.c=$(SRCS)%.o)
NAME 		= push_swap
BONUS_SRC	= checker.c \
			  init_stacks.c \
			  operations.c \
			  instructions_bonus.c \
			  utils.c \
			  print.c \
			  cleaner.c \
			  debug.c
BONUS_OBJS 	= $(BONUS_SRC:%.c=$(SRCS)%.o)
BONUS		= checker


all: $(NAME) $(BONUS)

bonus: $(BONUS)

$(NAME): $(OBJS)
	$(CC) $(CC_FLAGS) -I $(HEADS) $(OBJS) -o $(NAME)

$(BONUS): $(BONUS_OBJS)
	$(CC) $(CC_FLAGS) -I $(HEADS) $(BONUS_OBJS) -o $(BONUS)

$(BONUS_OBJS): | $(SRCS)

$(OBJS): | $(SRCS)

$(SRCS)%.o: $(SRCS)%.c
	$(CC) $(CC_FLAGS) -I $(HEADS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) $(BONUS_OBJS)
		
fclean:	clean
	$(RM) $(NAME)
	$(RM) $(BONUS)
				
re: fclean all

norm:
	$(NORMINETTE) $(SRCS)
	$(NORMINETTE) $(HEADS)

.PHONY:	all clean fclean re norm libft
