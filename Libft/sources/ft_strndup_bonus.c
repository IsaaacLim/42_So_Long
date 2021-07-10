#include "libft.h"

char	*ft_strndup(const char *s1, size_t dstsize)
{
	char	*dst;
	size_t	len;
	size_t	i;

	len = 0;
	while (s1[len] && len < (dstsize - 1))
		len++;
	dst = (char *)malloc(len * sizeof(char) + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (s1[i] && i < (dstsize - 1))
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
