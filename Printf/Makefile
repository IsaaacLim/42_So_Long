NAME 	=	libftprintf.a

LIBDIR	=	./libft
SRCDIR	=	./source
INCLUDES = 	./includes

SRCS	=	$(SRCDIR)/ft_printf.c	\
			$(SRCDIR)/pf_format.c	$(SRCDIR)/pf_length_mod.c \
			$(SRCDIR)/pf_modify.c	$(SRCDIR)/pf_output_alpha.c \
			$(SRCDIR)/pf_output_num.c

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc
CFLAGS	=	-c -Wall -Werror -Wextra -I

all:	$(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^
	make clean

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
