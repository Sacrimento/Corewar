#include "../include/corewar.h"

void 	inttounsignedchar(int n, unsigned char *map)
{
	map[0] = (n >> 24) & 0xFF;
	map[1] = (n >> 16) & 0xFF;
	map[2] = (n >> 8) & 0xFF;
	map[3] = n & 0xFF;
}

int main(void)
{
	t_vm		*vm = ft_memalloc(sizeof(t_vm));
	t_champ		*🅱️hampion = ft_memalloc(sizeof(t_champ));
	t_process	*process = ft_memalloc(sizeof(t_process));

	if (!vm || !(vm->map = (unsigned char *)ft_memalloc(MEM_SIZE)))
		ERROR("Cannot initiate test");
	vm->map[0] = 1;
	vm->map[1] = 1;
	🅱️hampion->id = 1;
	vm->champ = 🅱️hampion;
	ft_strcat(🅱️hampion->name, "tamere");
	inttounsignedchar(1, &vm->map[1]);
	if (!continue_process(vm, process))
		ERROR("FAIL");
}
