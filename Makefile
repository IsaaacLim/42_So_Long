NAME		=	so_long

SRCS_DIR	=	./sources/
SRCS_LST	=	exit.c			ft_control_hook.c	ft_init_vars.c 	\
				ft_move_en.c 	ft_move_pc.c		ft_parse_map.c	\
				ft_xpm_img.c	obj_enemy.c			obj_others.c	\
				obj_player.c	so_long.c      
SRCS 		=	$(addprefix $(SRCS_DIR), $(SRCS_LST))

OBJS		=	$(SRCS:.c=.o)

HDRS_DIR	=	./includes/
HRDS_LST	=	so_long.h
HDRS		=	$(addprefix $(HDRS_DIR), $(HRDS_LST))

MLX_DIR		=	./mlx_linux/
MLX			=	$(MLX_DIR)libmlx.a
MLX_LIB		=	-L. -lmlx -lm -lbsd -lX11 -lXext

LIBFT_DIR	=	./libft/
LIBFT		=	$(LIBFT_DIR)/libft.a
LIBFT_HDRS	=	$(LIBFT_DIR)includes/

INCLUDES	=	-I $(HDRS_DIR) -I $(LIBFT_HDRS) -I $(MLX_DIR)

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g3

all : $(MLX) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(LIBFT) -o $@
	@echo " $(YELLOW)$(NAME) $(GREEN)object files created"
	@echo " $(BLUE)$(NAME)$(GREEN) created$(RESET)"

$(SRCS_DIR)%.o : $(SRCS_DIR)%.c $(HDRS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

bonus:	re

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJS)
	@echo "$(RED)removed $(YELLOW)$(NAME) $(RED)object files $(RESET)"

fclean: clean
	@make clean -C $(MLX_DIR)
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "$(RED)removed $(BLUE)$(NAME)$(RESET)"

re: fclean all

.PHONY:	all clean fclean re bonus

RED		=	\033[00;31m
YELLOW	=	\033[03;33m
GREEN	=	\033[00;32m
BLUE	=	\033[01;36m
RESET	=	\033[0m
