# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/22 14:06:43 by lumenthi          #+#    #+#              #
#    Updated: 2018/03/03 10:48:21 by lumenthi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = gcc
FLAGS = -Wall -Werror -Wextra

LIBDIR = libft
SRCDIR = src
INCDIR = includes libft
OBJDIR = objs

LIBFT = $(LIBDIR)/libft.a
LIBFT_OBJ = $(LIBDIR)/objs

SRCS = args.c \
		args_sort.c \
		error.c \
		fill.c \
		fill_tool.c \
		first_print.c \
		ft_ls.c \
		global_tool.c \
		l_tool.c \
		l_tool2.c \
		ls.c \
		ls_l.c \
		ls_r.c \
		main.c \
		sort.c \
		sort_tool.c

SOURCES = $(addprefix $(SRCDIR)/, $(SRCS))
INCLUDES = $(addprefix -I, $(INCDIR))
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

GREEN = '\033[4;32m'
RED = '\033[4;31m'
BLANK = '\033[0m'
YELLOW = '\033[4;33m'

TICK = '\033[1;32m~\033[0m'
CROSS = '\033[1;31mx\033[0m'

.PHONY : all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@ $(CC) $(LIBFT) -o $(NAME) $(OBJS)
	@ printf " %b | Compiled %b%b%b\n" $(TICK) $(GREEN) $(NAME) $(BLANK)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ mkdir -p $(OBJDIR)
	@ $(CC) -c $(FLAGS) $(INCLUDES) -o $@ $<

$(LIBFT): $(LIBFT_OBJ)
	@ make -sC $(LIBDIR)

$(LIBFT_OBJ):
	@ make -sC $(LIBDIR)

clean:
	@ make -C $(LIBDIR) clean
	@ test -d $(OBJDIR) && \
	rm -rf $(OBJDIR) && \
	printf " %b | " $(TICK) && \
	printf "Removed %b%b%b object folder\n" $(YELLOW) $(NAME) $(BLANK) \
	|| (printf " %b | " $(CROSS) && \
	printf "No %b%b%b object folder\n" $(YELLOW) $(NAME) $(BLANK))

fclean: clean
	@ test -f $(LIBFT) && \
	rm -rf $(LIBFT) && \
	printf " %b | " $(TICK) && \
	printf "Removed %blibft%b library\n" $(RED) $(BLANK) \
	|| (printf " %b | " $(CROSS) && \
	printf "No %blibft%b library\n" $(RED) $(BLANK))
	@ test -f $(NAME) && \
	rm -rf $(NAME) && \
	printf " %b | " $(TICK) && \
	printf "Removed %b%b%b executable\n" $(RED) $(NAME) $(BLANK) \
	|| (printf " %b | " $(CROSS) && \
	printf "No %b%b%b executable\n" $(RED) $(NAME) $(BLANK))

re: fclean all
