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
	char *data = NULL, buf[BUFFER_SIZE]; // указатель data всегда указывает на 1 элемента data, мы его нигде не двигаем!!
	ssize_t r;

	while ((r = read(0, buf, BUFFER_SIZE)) > 0) // читаем в буфер пока не выдаст ошибку/не кончится
	{
		char *tmp = realloc(data, total + r + 1); // реаллоцируем дату и сохраняем новый указатель во временной переменной
												  // старый указатель на дату остается прежним
		if (!tmp)
		{
			perror("Error");
			free(data); // free(NULL) is ok, 
			return 1;
		}
		data = tmp; // а вот теперь кладем новый указатель
		memcpy(data + total, buf, r); // после реаллокации уже можно положить новые значения, но начиная с элемента data + total)
									  // !!!указатель на data остается тем же самым, там просто меняются values

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
		// счетчик i двигается вправо от начала строки "стога", поэтому каждый раз уменьшаем тотал 

		if (!m)
		{
			write(1, data + i, total - i); // не нашли нужную подстроку - знач совпадений нет, распечатываем оставшееся
			break; // и выходим из цикла
		}
		// метч найден!! тогда: 
		// выводим все до мэтча:
		write(1, data + i, m - (data + i)); // 3й аргумент - разница между началом "запиканного" и элемента "стога" с которого началась проверка

		size_t j = 0;
		while (j < nlen) // просто распечатываем звездочки nlen раз
		{
			write(1, "*", 1); 
			j++;
		}
		/* 
		сдвигаем i: разница между текущей подстрокой с которой начинается "иголка" и началом "стога"
		плюс длина "иголки" (распечатали)
		*/
		i = (m - data) + nlen;
	}
	free(data);

	return 0;
}
