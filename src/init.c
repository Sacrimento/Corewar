#include "corewar.h"

static int  check_champs_length(int argc, char **argv)
{
	//Check si les champs > 0 bytes && < a max_size
	return (0);
}

int			check_inputs(int argc, char **argv)
{
	//Check des defsines d'op.h
	return (0);
}

t_vm		init_vm(int argc, char **argv)
{
	t_vm		*vm;
	t_champs	*champs;

	if (!(champs = init_champs(argc, argv) || check_champs_length(champs)))
		return (0); //Pas forcement malloc
	if (!(vm = (t_vm*)ft_memalloc(sizeof(t_vm))))
		return (error_mall(0));
	if (!(vm->map = (unsigned char *)ft_memalloc(MEM_SIZE - 1)))
		return (error_mall(0));
	vm->opt = opt;
	vm->processes_nbr = 0;
	vm->cycle = 0;
	vm->champs = champs;
	vm->processes= NULL;
	load_champs(vm);
}