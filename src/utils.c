#include "./folder_sync_c.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *str;
	unsigned int i;
	unsigned int j;

	j = 0;
	i = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	while (*s1)
		str[j++] = *s1++;
	while (*s2)
		str[j++] = *s2++;
	str[j] = 0;
	return (str);
}

char *ft_strcat(char *dest, char *src)
{
	int i = 0;
	int j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

long ft_strlen(char *str)
{
	long i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void ft_putstr_fd(int fd, char *str)
{
	while (*str)
		write(fd, str++, 1);
}

int is_digit(char *str)
{
	while (*str)
	{
		if (*str != '+' && *str != '-' && (*str > '9' || *str < '0'))
			return (1);
		str++;
	}
	return (0);
}

int ft_atoi(char *str)
{
	int i = 0;
	long ret = 0;
	int negative = 1;

	while (str[i] != '\0' && (str[i] == '+' || str[i] == '-'))
		if (str[i++] == '-')
			negative = negative * -1;
	while (str[i] != '\0')
	{
		ret = (ret*10) + (str[i] - '0');
		i++;
	}
	if (ret > INT_MAX)
		return (INT_MAX);
	if (ret < INT_MIN)
		return (INT_MIN);
	return ((int)ret * negative);
}

static int nb_len(long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		len++;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char *ft_itoa(int n)
{
	char	*str;
	long	num;
	int		i;

	num = n;
	i = nb_len(num);
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (num == 0)
		str[0] = '0';
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	while (num > 0)
	{
		str[i] = '0' + (num % 10);
		num /= 10;
		i--;
	}
	return (str);
}
