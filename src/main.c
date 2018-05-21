#include "corewar.h"

int		main(int argc, char **argv)
{
	t_vm	*vm;
	int 	opt;

	if ((opt = set_opt(argc, argv)) == -1 || check_inputs(argc, argv))
		return (1);
	if (!(vm = init_vm(argc, argv, opt)))
		return (free_vm(vm));
	free_vm(vm);
	return (0);
}