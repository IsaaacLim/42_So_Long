#include "libft.h"

static int	ft_base_num_len(unsigned long long dec_num)
{
	int					hex_len;
	unsigned long long	remainder;

	hex_len = 1;
	remainder = dec_num / 16;
	while (remainder > 0)
	{
		remainder /= 16;
		hex_len++;
	}
	return (hex_len);
}

char	*ft_ulltoa_hex(unsigned long long dec_num)
{
	char	*hex_alpha;
	int		hex_len;
	int		rev;

	hex_len = ft_base_num_len(dec_num);
	hex_alpha = (char *)malloc((hex_len + 1) * sizeof(char));
	if (!hex_alpha)
		return (NULL);
	rev = hex_len;
	while (--rev >= 0)
	{
		hex_alpha[rev] = "0123456789abcdef"[dec_num % 16];
		dec_num /= 16;
	}
	hex_alpha[hex_len] = '\0';
	return (hex_alpha);
}
