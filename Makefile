NAME	=	so_long

SRCS	=	main.c
OBJS	=	$(SRCS:%.c=%.o)
INCLUDE	=	so_long.h

CC		=	gcc
#CFLAGS	=	-c -Wall -Werror -Wextra -g3 #(exclude -c?)

MLX		=	-L. -lmlx -lm -lbsd -lX11 -lXext
MLXDIR	=	mlx_linux
MLXLIB	=	$(MLXDIR)/libmlx.a

all : $(MLXLIB) $(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	$(CC) -o $@ $(SRCS) $(MLX) #must be (OBJS)?

$(MLXLIB):
	make -C $(MLXDIR)/

# From 42Docs > Getting Started
## To link with the required internal Linux API
#$(NAME): $(OBJS)
#	$(CC) -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
## For object files (Doesn't seem to matter if it's used/not)
#%.o: %.c
#	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	make clean -C $(MLXDIR)/
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
