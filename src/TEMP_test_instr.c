#include "../include/corewar.h"

void 	inttounsignedchar(int n, unsigned char *map)
{
	map[0] = (n >> 24) & 0xFF;
	map[1] = (n >> 16) & 0xFF;
	map[2] = (n >> 8) & 0xFF;
	map[3] = n & 0xFF;
}

int		live(t_vm *vm, t_process *process, t_param *params)
{
	t_champ *thischamp;

	if (!vm || !vm->champ
	|| !(thischamp = get_champ_by_num(vm->champ, (params[1]).value)))
		return (0);
	thischamp->lives++;
	ft_printf("[%d]{BLUE}Champion %s(id:%d) is alive{EOC}",
		thischamp->lives, thischamp->name, thischamp->id);
	return (process->alive = 1);
}

int main(void)
{
	t_vm *vm = ft_memalloc(sizeof(t_vm));
	t_champ *cham🅱️ion = ft_memalloc(sizeof(t_champ));
	t_process *process = ft_memalloc(sizeof(t_process));

	if (!(vm->map = (unsigned char *)ft_memalloc(MEM_SIZE)))
		ERROR("Cannot initiate test");
	vm->map[0] = 01;
	inttounsignedchar(1, &vm->map[1]);
	cham🅱️ion->id = 1;
	ft_strcat("tamere", cham🅱️ion->name);

	
	live(vm, process, get_params(vm, process));
}

