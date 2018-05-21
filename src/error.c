#include "corewar.h"

int		error_mall(int err)
{
	ft_putstr_fd("Erreur d'allocation memoire\n", 2);
	return (err); 
}

int		usage(void)
{
	ft_putstr_fd("Coucou c'est l'usage\n", 2);
	return (0);
}