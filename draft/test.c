#include <stdio.h>

int	main(void)
{
	char str[] = "hello";

	int i;

	i = 0;
	while (i < 20)
	{
		if (str[i])
			printf("%s\n", str + i);
		i++;
	}
}