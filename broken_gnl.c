/*

--------------------------------------

NOT FIXED YET!!! IN PROGRESS!!!

--------------------------------------

*/

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;	

	d = (char *)dest;
	s = (const char *)src;
	if ((d == NULL && s == NULL) || n == 0)
		return (dest);
	while (n-- > 0)
		*d++ = *s++;
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1;
	char	*tmp;

	size1 = ft_strlen(*s1);
	tmp = malloc (size1 + size2 + 1);
	if (!tmp)
		return (0);
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return (1);
}

int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2))); //
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = (char *)dest;
	s = (const char *)src;
	if ((d == NULL && s == NULL) || n == 0)
		return (dest);
	if (d > s && d < s + n)
	{
		d += n - 1;
		s += n - 1;
		while (n--)
			*d-- = *s--;
	}
	else
	{
		while (n--)
			*d++ = *s++;
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	b[BUFFER_SIZE] = " ";
	char		*ret = NULL;
	char		*tmp;
	int			read_ret = read(fd, b, BUFFER_SIZE); // bytes read check
	int			i = 0;

	tmp = ft_strchr(b, '\n');
	while (i <= BUFFER_SIZE)
	{
		if (!str_append_str(&ret, b)) // malloc fail check
			return (NULL);
		if (read_ret = NULL); // read fail check
			return (NULL);
		b[read_ret] = 0; // null terminator
		i++;
	}
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

// int	main(void)
// {
// 	int	fd = open("file2", O_RDONLY);
// 	char	*line;
// 	line = NULL;
// 	while(fd > 0)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		printf("Line: %s\n", line);
// 	}
// 	free(line);
// }
