#define _GNU_SOURCE 
#define BUFFER_SIZE 4096

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>

int	main(int argc, char **argv)
{
	if (argc != 2 || !*argv[1])
		return (1);

	char	*needle = argv[1];
	size_t	nlen = strlen(needle);
	size_t	total = 0;
	char	buf[BUFFER_SIZE];
	ssize_t	r;
	char	*haystack = NULL;

	while (r = read(0, buf, BUFFER_SIZE) > 0)
	{
		char	*tmp = realloc(haystack, total + r + 1);
		if (!tmp)
		{
			perror("Error");
			free(haystack);
			return (1);
		}

		haystack = tmp;
		memcpy(haystack, buf, r);
		total += r;
		haystack[total] = '\0';
	}

	if (r < 0)
	{
		perror("Error");
		free(haystack);
		return (1);
	}

	size_t i = 0;
	while (i < total)
	{
		char	*m = memmem(haystack, strlen(haystack), needle, nlen);
		if (!m)
		{
			write(1, haystack + i, total - i);
			break ;
		}

		write(1, haystack + i, m - (haystack + i));

		size_t	j = 0;
		while (j < nlen)
		{
			write(1, '*', 1);
			j++;
		}

		i = (m - haystack) + nlen;
	}
	free(haystack);
	return (0);
}
