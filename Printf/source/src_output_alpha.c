#include "../includes/ft_printf.h"

void	ft_output_char(t_print *info)
{
	char	letter;

	letter = va_arg(info->args, int);
	info->argument_length = 1;
	if (info->width && !info->dash)
		ft_mod_right_alpha(info);
	info->total_length += ft_putchar(letter);
	if (info->width && info->dash)
		ft_mod_left(info);
}

void	ft_output_string(t_print *info)
{
	char	*string;
	char	*temp;

	string = va_arg(info->args, char *);
	if (!string)
		string = "(null)";
	if (info->has_precision)
	{
		if (info->precision == 0)
			temp = ft_calloc(1, 1);
		else if (info->precision < (int)ft_strlen(string))
			temp = ft_strndup(string, (info->precision + 1));
		else
			temp = ft_strdup(string);
		string = temp;
	}
	info->argument_length = ft_strlen(string);
	if (info->width && !info->dash)
		ft_mod_right_alpha(info);
	info->total_length += ft_putstr(string);
	if (info->width && info->dash)
		ft_mod_left(info);
	if (info->has_precision)
		free(string);
}

void	ft_output_nothing(t_print *info)
{
	signed char	*sc_num;
	short		*s_num;
	int			*i_num;
	long		*l_num;

	if (info->len_mod_h)
	{
		s_num = va_arg(info->args, short *);
		*s_num = info->total_length;
	}
	else if (info->len_mod_hh)
	{
		sc_num = va_arg(info->args, signed char *);
		*sc_num = info->total_length;
	}
	else if (info->len_mod_l || info->len_mod_ll)
	{
		l_num = va_arg(info->args, long *);
		*l_num = info->total_length;
	}
	else
	{	
		i_num = va_arg(info->args, int *);
		*i_num = info->total_length;
	}
}
