NAME	=	libft.a

SRCS_DIR	=	./sources/
SRCS_LST	=	ft_atoi.c		ft_bzero.c		ft_calloc.c		ft_isdigit.c \
				ft_memcpy.c		ft_split.c		ft_strchr.c		ft_strdup.c	 \
				ft_strjoin.c	ft_strlcpy.c	ft_strlen.c 	ft_strnstr.c \
				ft_substr.c
SRCS_B_LST	=	ft_lltoa_bonus.c	ft_putchar_bonus.c	ft_putstr_bonus.c	 \
				ft_strndup_bonus.c 	ft_tco_bonus.c		ft_toupper_bonus.c	 \
				ft_ulltoa_bonus.c	ft_ulltoa_hex_bonus.c
GNL_LST		=	get_next_line.c
SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_LST) $(SRCS_B_LST) $(GNL_LST))

OBJS		= 	$(SRCS:.c=.o)

HDRS_DIR	=	./includes/
HRDS_LST	=	libft.h
HDRS		=	$(addprefix $(HDRS_DIR), $(HRDS_LST))

INCLUDES	= 	-I $(HDRS_DIR)

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g3

all:		$(NAME) 

$(NAME):	$(OBJS)
	ar rcs $@ $^
#make clean

$(SRCS_DIR)%.o : $(SRCS_DIR)%.c $(HDRS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJS)

fclean:		clean
	rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
