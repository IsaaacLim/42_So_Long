NAME	=	so_long

TEST	=	test
TEST_S	=	test.c
TEST_O	=	$(TEST_S:%.c=%.o)

SRCS	=	main.c controls.c extra_func.c ft_readfile.c
OBJS	=	$(SRCS:%.c=%.o)
INCLUDE	=	so_long.h

CC		=	gcc -g #-g for debugging
#CFLAGS	=	-c -Wall -Werror -Wextra -g3 #(exclude -c?)

MLX		=	-L. -lmlx -lm -lbsd -lX11 -lXext
MLXDIR	=	mlx_linux
MLXLIB	=	$(MLXDIR)/libmlx.a

GNLDIR	=	GetNextLine
GNL		=	$(GNLDIR)/GNL.a

LIBDIR	=	Libft
LIBFT	=	$(LIBDIR)/libft.a

PRINTFDIR	=	Printf
PRINTF		=	$(PRINTFDIR)/libftprintf.a

all : $(LIBFT) $(PRINTFDIR) $(GNL) $(MLXLIB) $(NAME) $(TEST)

$(NAME): $(OBJS) $(INCLUDE)
	$(CC) $(SRCS) $(MLX) $(GNL) $(PRINTF) $(LIBFT) -o $@ 
#must be (OBJS)?

$(LIBFT):
	make -C $(LIBDIR)

$(GNL):
	make -C $(GNLDIR)

$(PRINTF):
	make -C $(PRINTFDIR)

$(MLXLIB):
	make -C $(MLXDIR)/

$(TEST): $(TEST_O)
	$(CC) -o $@ $(TEST_S) $(MLX)

clean:
	rm -f $(OBJS)
	rm -f $(TEST_O)

fclean: clean
	make clean -C $(MLXDIR)/
	rm -f $(NAME)
	rm -f $(TEST)
	make fclean -C $(LIBDIR)
	make fclean -C $(GNLDIR)
	make fclean -C $(PRINTFDIR)
#REMOVE TEST

re: fclean all

.PHONY:	all clean fclean re
