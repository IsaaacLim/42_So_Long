NAME	=	GNL.a

SRCS	=	get_next_line.c	get_next_line_utils.c
OBJS	=	$(SRCS:.c=.o)

CC		=	gcc
CFLAGS	=	-c -Wall -Werror -Wextra

all:	$(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^
	make clean

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re