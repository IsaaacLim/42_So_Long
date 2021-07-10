NAME	=	so_long

SRCDIR	=	./source/
SRC_LIST=	exit.c			ft_control_hook.c	ft_init_vars.c 	ft_move_en.c \
			ft_move_pc.c	ft_parse_map.c		ft_xpm_img.c	obj_enemy.c	 \
			obj_others.c	obj_player.c		so_long.c      
SRCS 	=	$(addprefix $(SRCDIR), $(SRC_LIST))

OBJS	=	$(SRCS:.c=.o)
HEADER	=	./includes/so_long.h
INCLUDES=	-I ./includes/

CC		=	gcc -g3
CFLAGS	=	-Wall -Werror -Wextra

MLX		=	-L. -lmlx -lm -lbsd -lX11 -lXext
MLXDIR	=	mlx_linux
MLXLIB	=	$(MLXDIR)/libmlx.a

LIBDIR	=	Libft
LIBFT	=	$(LIBDIR)/libft.a

PRINTFDIR	=	Printf
PRINTF		=	$(PRINTFDIR)/libftprintf.a

all : $(LIBFT) $(PRINTF) $(MLXLIB) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(PRINTF) $(LIBFT) -o $@ 

$(SRCDIR)%.o : $(SRCDIR)%.c $(HEADER)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	make -C $(LIBDIR)

$(PRINTF):
	make -C $(PRINTFDIR)

$(MLXLIB):
	make -C $(MLXDIR)

clean:
	rm -f $(OBJS)

fclean: clean
	make clean -C $(MLXDIR)
	rm -f $(NAME)
	make fclean -C $(LIBDIR)
	make fclean -C $(PRINTFDIR)

re: fclean all

.PHONY:	all clean fclean re
