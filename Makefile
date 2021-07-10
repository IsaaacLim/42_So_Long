NAME		=	so_long

SRCS_DIR	=	./sources/
SRCS_LST	=	exit.c			ft_control_hook.c	ft_init_vars.c 	\
				ft_move_en.c 	ft_move_pc.c		ft_parse_map.c	\
				ft_xpm_img.c	obj_enemy.c			obj_others.c	\
				obj_player.c	so_long.c      
SRCS 		=	$(addprefix $(SRCS_DIR), $(SRCS_LST))

OBJS		=	$(SRCS:.c=.o)

HDRS_DIR	=	./includes/
HEADER		=	./includes/so_long.h
INCLUDES	=	-I ./includes/

MLX		=	-L. -lmlx -lm -lbsd -lX11 -lXext
MLXDIR	=	mlx_linux
MLXLIB	=	$(MLXDIR)/libmlx.a

LIBDIR	=	Libft
LIBFT	=	$(LIBDIR)/libft.a

CC		=	gcc -g3
CFLAGS	=	-Wall -Werror -Wextra

all : $(LIBFT) $(MLXLIB) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT) -o $@ 

$(SRCDIR)%.o : $(SRCDIR)%.c $(HEADER)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	make -C $(LIBDIR)

$(MLXLIB):
	make -C $(MLXDIR)

clean:
	rm -f $(OBJS)

fclean: clean
	make clean -C $(MLXDIR)
	rm -f $(NAME)
	make fclean -C $(LIBDIR)

re: fclean all

.PHONY:	all clean fclean re
