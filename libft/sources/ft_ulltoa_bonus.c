#include "libft.h"

static int	ft_ull_len(unsigned long long n)
{
	int	len;

	len = 0;
	if (n == 0)
		len += 1;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_ulltoa(unsigned long long n)
{
	int		ull_len;
	char	*str;

	ull_len = ft_ull_len(n);
	str = ft_calloc(ull_len + 1, 1);
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	while (n)
	{
		str[ull_len-- - 1] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
