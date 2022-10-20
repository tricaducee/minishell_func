#include <stdio.h>

int	main(int ac, char **av)
{
	int	i = 0;
	printf("%d argument(s)\n", ac - 1);
	while (av[++i])
		printf("%d : %s\n", i - 1, av[i]);
	return (0);
}
