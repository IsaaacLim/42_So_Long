NAME		=	libft.a

SRCS_DIR	=	./sources/
SRCS_LST	=	ft_atoi.c			ft_bzero.c			ft_calloc.c			\
				ft_isdigit.c		ft_memcpy.c			ft_split.c			\
				ft_strchr.c			ft_strdup.c			ft_strjoin.c		\
				ft_strlcpy.c		ft_strlen.c 		ft_strnstr.c		\
				ft_substr.c
SRCS_B_LST	=	ft_lltoa_bonus.c	ft_putchar_bonus.c	ft_putstr_bonus.c	\
				ft_strndup_bonus.c 	ft_tco_bonus.c		ft_toupper_bonus.c	\
				ft_ulltoa_bonus.c	ft_ulltoa_hex_bonus.c
GNL_LST		=	get_next_line.c
PNTF_LST	=	ft_printf.c			pf_format.c			pf_length_mod.c		\
				pf_modify.c			pf_output_alpha.c	pf_output_num.c
SRCS		=	$(addprefix $(SRCS_DIR), \
				$(SRCS_LST) $(SRCS_B_LST) $(GNL_LST) $(PNTF_LST))

OBJS		= 	$(SRCS:.c=.o)

HDRS_DIR	=	./includes/
HRDS_LST	=	libft.h get_next_line.h ft_printf.h
HDRS		=	$(addprefix $(HDRS_DIR), $(HRDS_LST))

INCLUDES	= 	-I $(HDRS_DIR)

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g3

all:		$(NAME) 

$(NAME):	$(OBJS)
	@ar rcs $@ $^
	@echo " $(YELLOW)$(NAME) $(GREEN)object files created"
	@echo " $(BLUE)$(NAME)$(GREEN) created$(RESET)"
#make clean

$(SRCS_DIR)%.o : $(SRCS_DIR)%.c $(HDRS)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

clean:
	@rm -rf $(OBJS)
	@echo "$(RED)removed $(YELLOW)$(NAME) $(RED)object files $(RESET)"

fclean:		clean
	@rm -rf $(NAME)
	@echo "$(RED)removed $(BLUE)$(NAME)$(RESET)"

re:			fclean all

.PHONY:		all clean fclean re

RED		=	\033[00;31m
YELLOW	=	\033[03;33m
GREEN	=	\033[00;32m
BLUE	=	\033[01;36m
RESET	=	\033[0m