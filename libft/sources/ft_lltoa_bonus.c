#include "libft.h"
#include <limits.h>

static int	ft_num_len(long long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len += 1;
		n *= -1;
	}
	if (n == 0)
		len += 1;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_lltoa(long long n)
{
	int		num_len;
	char	*str;

	num_len = ft_num_len(n);
	str = ft_calloc(num_len + 1, 1);
	if (!str)
		return (NULL);
	if (n == LLONG_MIN)
	{
		str[num_len-- - 1] = '8';
		n /= 10;
	}
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	if (n == 0)
		str[0] = '0';
	while (n)
	{
		str[num_len-- - 1] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
