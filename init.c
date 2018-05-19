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
		return (error(CHAMP_LEN_ERROR));
	if (!(vm = (t_vm*)malloc(sizeof(t_vm))))
		return (error(MALLOC_ERR, 0, 0, 0));
	if (!(vm->map = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE)))
		return (error(MALLOC_ERR, 0, 0, 0));
	vm->opt = opt;
}