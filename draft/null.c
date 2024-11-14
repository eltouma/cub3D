#include <stdbool.h>

void	fct_qui_mofie_tab(char ***tab)
{
	printf("tab dans la fct avant d'etre mofie == %p\n", *tab);
	free(*tab);
	// *tab = 0;
	printf("tab dans la fct apres avoir ete mofie == %p\n", *tab);
}

int	main(int argc, char **argv)
{
	char **tab = malloc((argc == 1) ? 10 : 5 * sizeof(char *));
	for (int i = 0; i < 10; i++)
	{
		tab[i] = malloc(10);
	}
	printf("tab == %p\n", tab);
	fct_qui_mofie_tab(&tab);
	printf("tab == %p\n", tab);
	// free(tab);
}