#define _GNU_SOURCE
#define BUFFER_SIZE 4096

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>

int main(int argc, char **argv)
{
	if (argc != 2 || !*argv[1])
		return 1;

	char *needle = argv[1];
	size_t nlen = strlen(needle), total = 0;
	char *data = NULL, buf[BUFFER_SIZE];
	ssize_t r;

	while ((r = read(0, buf, BUFFER_SIZE)) > 0) // читаем в буфер пока не выдаст ошибку/не кончится
	{
		char *tmp = realloc(data, total + r + 1);
		if (!tmp)
		{
			perror("Error");
			free(data); // free(NULL) is ok, 
			return 1;
		}
		data = tmp;
		memcpy(data + total, buf, r); // копир
		total += r; // длина дата всего на данной итерации
		data[total] = '\0'; 
	}

	if (r < 0)
	{
		perror("Error");
		free(data);
		return 1;
	}

	size_t i = 0;
	while (i < total) // распечатываем если найдено строку
	{
		char *m = memmem(data + i, total - i, needle, nlen); // ищем подстроку начиная с самого первого элемента, memmem ищет подстроку, все просто
		if (!m)
		{
			write(1, data + i, total - i);
			break;
		}

		write(1, data + i, m - (data + i));

		size_t j = 0;
		while (j < nlen)
		{
			write(1, "*", 1);
			j++;
		}

		i = (m - data) + nlen;
	}
	free(data);

	return 0;
}
