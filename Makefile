NAME	=	so_long

SRCDIR	=	./source/

SRC_LIST=	exit.c			ft_control_hook.c	ft_init_vars.c 	ft_move_en.c \
			ft_move_pc.c	ft_parse_map.c		ft_xpm_img.c	obj_enemy.c	 \
			obj_others.c	obj_player.c		so_long.c      
SRCS 	=	$(addprefix $(SRCDIR), $(SRC_LIST))

OBJS	=	$(SRCS:.c=.o)
INCLUDE	=	so_long.h

CC		=	gcc -g #-g for debugging
CFLAGS	=	-c -Wall -Werror -Wextra -I#-g3 #(exclude -c?)

MLX		=	-L. -lmlx -lm -lbsd -lX11 -lXext
MLXDIR	=	mlx_linux
MLXLIB	=	$(MLXDIR)/libmlx.a

GNLDIR	=	GetNextLine
GNL		=	$(GNLDIR)/GNL.a

LIBDIR	=	Libft
LIBFT	=	$(LIBDIR)/libft.a

PRINTFDIR	=	Printf
PRINTF		=	$(PRINTFDIR)/libftprintf.a

all : $(LIBFT) $(PRINTF) $(GNL) $(MLXLIB) $(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	$(CC) $(OBJS) $(MLX) $(GNL) $(PRINTF) $(LIBFT) -o $@ 
#must be (OBJS)?

$(LIBFT):
	make -C $(LIBDIR)

$(GNL):
	make -C $(GNLDIR)

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
	make fclean -C $(GNLDIR)
	make fclean -C $(PRINTFDIR)

re: fclean all

.PHONY:	all clean fclean re
