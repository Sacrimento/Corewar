#include "coreawar.h"

int		main(int argc, char **argv)
{
	t_vm	vm;
	int 	opt;

	if ((opt = set_opt(argc, argv)) == -1 || check_inputs(ac, av))
		return (1);
	if (!(vm = init_vm(argc, argv, opt)))
		return (1);
	return (0);
}