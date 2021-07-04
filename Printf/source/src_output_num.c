#include "../includes/ft_printf.h"

/*
** Print sequence:	| Criteria:
** 1. right spaces	| !dash && (width > num_len && width > precision + neg)
** 2. neg sign		| num < 0
** 3. zeros			| (zero && !precision) || precision > len(abs_num)
** 4. arg values	| absolute_num
** 5. left spaces	| width > len(absolute_num) && dash
**
** *. If has_precision && precision==0 && num == 0, nothing exist
**	
** Example:
** -000000123456$
**      -123456$
**   -0000123456$
** -0000123456$
** -123456$
** -123456      $
** -0001234     $
** 
** l == long
** ll == long long
** h = short
** hh = signed char
*/

static void	ft_output_blank(t_print *info)
{
	if (info->plus)
	{	
		if (info->dash)
			info->total_length += ft_putchar('+');
		while (info->width-- > 1)
			info->total_length += ft_putchar(' ');
		if (!info->dash)
			info->total_length += ft_putchar('+');
	}
	else if (info->space && info->width == 0)
		info->total_length += ft_putchar(' ');
	while (info->width-- > 0)
		info->total_length += ft_putchar(' ');
}

void	ft_output_int(t_print *info)
{
	int			neg;
	char		*itoa;
	long long	number;

	number = ft_length_modifier_id(info);
	if (info->has_precision && info->precision == 0 && number == 0)
		ft_output_blank(info);
	else
	{
		itoa = ft_lltoa(number);
		neg = 0;
		if (number < 0)
			neg = 1;
		ft_mod_right_digit(info, itoa, neg);
		info->argument_length += ft_putstr(&itoa[neg]);
		info->total_length += info->argument_length;
		ft_mod_left(info);
		free(itoa);
	}
}

void	ft_output_unsigned(t_print *info)
{
	char					*utoa;
	unsigned long long		number;

	number = ft_length_modifier_uxX(info);
	if (info->has_precision && info->precision == 0 && number == 0)
		ft_output_blank(info);
	else
	{	
		utoa = ft_ulltoa(number);
		ft_mod_right_digit(info, utoa, 0);
		info->argument_length += ft_putstr(utoa);
		info->total_length += info->argument_length;
		ft_mod_left(info);
		free(utoa);
	}
}

void	ft_output_hex(t_print *info)
{
	char				*utoa_hex;
	unsigned long long	number;

	number = ft_length_modifier_uxX(info);
	if (info->has_precision && info->precision == 0 && number == 0)
		ft_output_blank(info);
	else
	{
		utoa_hex = ft_ulltoa_hex(number);
		if (*info->format == 'X')
			ft_toupper(utoa_hex);
		if (info->hash && number != 0)
			ft_mod_right_pointer(info, utoa_hex);
		else
			ft_mod_right_digit(info, utoa_hex, 0);
		info->argument_length += ft_putstr(utoa_hex);
		info->total_length += info->argument_length;
		ft_mod_left(info);
		free(utoa_hex);
	}
}

void	ft_output_pointer(t_print *info)
{
	char				*ulltoa_hex;
	unsigned long long	number;

	number = (unsigned long long)va_arg(info->args, void *);
	ulltoa_hex = ft_ulltoa_hex(number);
	ft_mod_right_pointer(info, ulltoa_hex);
	info->argument_length += ft_putstr(ulltoa_hex);
	info->total_length += info->argument_length;
	ft_mod_left(info);
	free(ulltoa_hex);
}
