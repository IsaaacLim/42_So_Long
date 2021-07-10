#include "../includes/ft_printf.h"

void	ft_mod_right_alpha(t_print *info)
{
	while (info->width-- > info->argument_length)
	{
		if (info->zero && !info->has_precision)
			info->total_length += ft_putchar('0');
		else
			info->total_length += ft_putchar(' ');
	}
}

static void	ft_mod_right_digit2(t_print *info, char *itoa, int neg, int num_len)
{
	if (neg)
		info->argument_length += ft_putchar('-');
	else if (info->plus)
		info->argument_length += ft_putchar('+');
	else if (info->space)
		info->argument_length += ft_putchar(' ');
	if ((info->zero && !info->has_precision && !info->dash))
	{
		while (info->width-- > num_len)
			info->argument_length += ft_putchar('0');
	}
	else if (info->has_precision)
	{
		while (info->precision-- > (int)ft_strlen(&itoa[neg]))
			info->argument_length += ft_putchar('0');
	}
}

void	ft_mod_right_digit(t_print *info, char *itoa, int neg)
{
	int	num_len;
	int	gap;

	gap = neg;
	num_len = ft_strlen(itoa);
	if ((info->space || info->plus) && !neg)
	{
		num_len++;
		gap = 1;
	}
	if (!info->dash && (!info->zero || info->has_precision))
	{
		while (info->width > num_len && info->width-- > (info->precision + gap))
			info->argument_length += ft_putchar(' ');
	}
	ft_mod_right_digit2(info, itoa, neg, num_len);
}

void	ft_mod_right_pointer(t_print *info, char *ulltoa)
{
	int	num_len;

	num_len = ft_strlen(ulltoa) + 2;
	if (!info->dash && (!info->zero || info->has_precision))
	{
		while (info->width > num_len && info->width-- > (info->precision + 2))
			info->argument_length += ft_putchar(' ');
	}
	if (*info->format == 'X')
		info->argument_length += ft_putstr("0X");
	else
		info->argument_length += ft_putstr("0x");
	if ((info->zero && !info->has_precision && !info->dash))
	{
		while (info->width-- > num_len)
			info->argument_length += ft_putchar('0');
	}
	else if (info->has_precision)
	{
		while (info->precision-- > (int)ft_strlen(ulltoa))
			info->argument_length += ft_putchar('0');
	}
}

void	ft_mod_left(t_print *info)
{
	while (info->width-- > info->argument_length)
		info->total_length += ft_putchar(' ');
}
