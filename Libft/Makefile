NAME	=	libft.a

SRCS	=	ft_atoi.c		ft_bzero.c		ft_calloc.c		ft_isdigit.c	\
			ft_memcpy.c		ft_split.c		ft_strchr.c		ft_strdup.c		\
			ft_strjoin.c	ft_strlcpy.c	ft_strlen.c 	ft_strnstr.c	\
			ft_substr.c
SRCS_B	=	ft_lltoa_bonus.c	ft_putchar_bonus.c	ft_putstr_bonus.c		\
			ft_strndup_bonus.c 	ft_tco_bonus.c		ft_toupper_bonus.c		\
			ft_ulltoa_bonus.c	ft_ulltoa_hex_bonus.c	
OBJS	= 	$(SRCS:.c=.o)
OBJS_B	=	$(SRCS_B:.c=.o)

CC		=	gcc
CFLAGS	=	-c -Wall -Wextra -Werror -I

all:		$(NAME) 

$(NAME):	$(OBJS) $(OBJS_B)
	ar rcs $@ $^
	make clean

clean:
	rm -rf $(OBJS) $(OBJS_B)

fclean:		clean
	rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
