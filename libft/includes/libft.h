#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);

/*
** Bonus
*/
char	*ft_lltoa(long long n);
char	*ft_ulltoa(unsigned long long n);
char	*ft_ulltoa_hex(unsigned long long dec_num);
char	*ft_strndup(const char *s1, size_t dstsize);
int		ft_putchar(char c);
int		ft_putstr(char *string);
int		ft_tco_int(int yes, int yea, int nah);
void	*ft_tco_voidStr(int yes, void *yea, void *nah);
void	ft_toupper(char *string);
#endif
