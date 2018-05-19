#include "corewar.h"

int		error(int err, char illegal, int size_champ, int expected_size)
{
	if (err == MALLOC_ERR)
		return (ft_putstr_fd("Erreur d'allocation memoire\n", 2));
	if (err == OPT_ERR)
	{
		ft_putstr_fd("Option illegale : ", 2);
		write(2, illegal, 1);
		ft_putstr_fd("\n", 2);
		return (usage());
	}
	if (err == CHAMP_LEN_ERR)
	{
		
	}
}