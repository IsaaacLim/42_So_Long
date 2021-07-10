#include "../includes/ft_printf.h"

static void	ft_reset_arg_info(t_print *info)
{
	info->argument_length = 0;
	info->precision = 0;
	info->width = 0;
	info->dash = false;
	info->has_precision = false;
	info->hash = false;
	info->len_mod_h = false;
	info->len_mod_hh = false;
	info->len_mod_l = false;
	info->len_mod_ll = false;
	info->plus = false;
	info->space = false;
	info->zero = false;
}

int	ft_printf(const char *format, ...)
{
	t_print	*info;
	int		len;

	info = (t_print *)ft_calloc(1, sizeof(t_print));
	if (!info)
		return (-1);
	va_start(info->args, format);
	info->format = format;
	info->total_length = 0;
	while (*info->format)
	{
		while (*info->format != '%' && *info->format != '\0')
		{
			info->total_length += ft_putchar(*info->format);
			info->format++;
		}
		if (*info->format == '%')
			ft_format_flag(info);
		ft_reset_arg_info(info);
	}
	va_end(info->args);
	len = info->total_length;
	free(info);
	return (len);
}
