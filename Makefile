NAME	=	testtest

OBJ		=	test.c

CC		=	gcc


# From 42Docs > Getting Started
## To link with the required internal Linux API
$(NAME): $(OBJ)
	$(CC) -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
## For object files
%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@
