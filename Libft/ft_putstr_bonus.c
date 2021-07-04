#include "libft.h"

int	ft_putstr(char *string)
{
	int	ret;

	ret = 0;
	while (*string)
	{
		ret += write(1, string, 1);
		string++;
	}
	return (ret);
}
