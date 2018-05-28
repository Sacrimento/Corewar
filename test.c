#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	char			*alloc;
	unsigned int	count;

	count = 0;
	if ((alloc = (char*)malloc(sizeof(char) * size)) != NULL)
	{
		while (count < size)
			alloc[count++] = 0;
		return (alloc);
	}
	else
		return (NULL);
}
void	ft_bzero(void *s, size_t n)
{
	size_t count;

	count = 0;
	while (count < n)
		((unsigned char*)s)[count++] = 0;
}

typedef struct s_test
{
	int test;
	int test2;
	char *test3;
}				t_test;

int main(void)
{
	t_test test[3];

	ft_bzero(test, sizeof(t_test) * 3);
	if (test->test2 == 0)
		printf("caca");
}