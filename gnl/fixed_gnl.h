#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 42

char	*ft_strchr(const char* str, int c);
void	*memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char* s);
int		str_append_mem(char **s1, char *s2, size_t size2);
int		str_append_str(char **s1, char *s2);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*get_next_line(int fd);