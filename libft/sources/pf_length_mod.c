#include "../includes/ft_printf.h"

long long	ft_length_modifier_id(t_print *info)
{
	long long	number;

	number = va_arg(info->args, long long);
	if (info->len_mod_l)
		number = (long)number;
	else if (info->len_mod_h)
		number = (short)number;
	else if (info->len_mod_hh)
		number = (signed char)number;
	else if (!info->len_mod_ll)
		number = (int)number;
	return (number);
}

unsigned long long	ft_length_modifier_uxX(t_print *info)
{
	unsigned long long		number;

	number = va_arg(info->args, unsigned long long);
	if (info->len_mod_l)
		number = (unsigned long)number;
	else if (info->len_mod_h)
		number = (unsigned short)number;
	else if (info->len_mod_hh)
		number = (unsigned char)number;
	else if (!info->len_mod_ll)
		number = (unsigned int)number;
	return (number);
}
