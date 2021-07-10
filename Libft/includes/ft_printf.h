#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdbool.h>

typedef struct s_print
{
	va_list		args;
	const char	*format;
	int			argument_length;
	int			total_length;
	int			precision;
	int			width;
	bool		dash;
	bool		has_precision;
	bool		hash;
	bool		len_mod_h;
	bool		len_mod_hh;
	bool		len_mod_l;
	bool		len_mod_ll;
	bool		plus;
	bool		space;
	bool		zero;
}	t_print;

int					ft_printf(const char *format, ...);
void				ft_format_flag(t_print *info);
void				ft_mod_right_alpha(t_print *info);
void				ft_mod_right_digit(t_print *info, char *itoa, int neg);
void				ft_mod_right_pointer(t_print *info, char *ulltoa);
void				ft_mod_left(t_print *info);
void				ft_output_char(t_print *info);
void				ft_output_hex(t_print *info);
void				ft_output_int(t_print *info);
void				ft_output_nothing(t_print *info);
void				ft_output_pointer(t_print *info);
void				ft_output_string(t_print *info);
void				ft_output_unsigned(t_print *info);
long long			ft_length_modifier_id(t_print *info);
unsigned long long	ft_length_modifier_uxX(t_print *info);

#endif