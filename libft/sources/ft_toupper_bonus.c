#include "libft.h"

void	ft_toupper(char *string)
{
	if (!string)
		return ;
	while (*string)
	{
		if (*string >= 'a' && *string <= 'z')
			*string -= ' ';
		string++;
	}
}
