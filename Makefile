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

all : $(LIBFT) $(GNL) $(MLXLIB) $(NAME) $(TEST)

$(NAME): $(OBJS) $(INCLUDE)
	$(CC) $(SRCS) $(MLX) $(GNL) $(LIBFT) -o $@ 
#must be (OBJS)?

$(LIBFT):
	make -C $(LIBDIR)

$(GNL):
	make -C $(GNLDIR)

$(MLXLIB):
	make -C $(MLXDIR)/

$(TEST): $(TEST_O)
	$(CC) -o $@ $(TEST_S) $(MLX)

# From 42Docs > Getting Started
## To link with the required internal Linux API
#$(NAME): $(OBJS)
#	$(CC) -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
## For object files (Doesn't seem to matter if it's used/not)
#%.o: %.c
#	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(TEST_O)

fclean: clean
	make clean -C $(MLXDIR)/
	rm -f $(NAME)
	rm -f $(TEST)
#TEMP

re: fclean all

.PHONY:	all clean fclean re
