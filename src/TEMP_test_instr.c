#include "../include/corewar.h"

void 	inttounsignedchar(int n, unsigned char *map)
{
	map[0] = (n >> 24) & 0xFF;
	map[1] = (n >> 16) & 0xFF;
	map[2] = (n >> 8) & 0xFF;
	map[3] = n & 0xFF;
}

int		live(t_instr instr)
{
	t_champ *thischamp;

	if (!instr.vm->champ || !instr.params)
	{
		ERROR("paramerror");
		return (0);
	}
	if (!instr.vm || !instr.vm->champ
	|| !(thischamp = get_champ_by_num(instr.vm->champ, 
	instr.params[1].value)))
		return (0);
	thischamp->lives++;
	ft_printf("[%d]{BLUE}Champion %s(id:%d) is alive{EOC}",
		thischamp->lives, thischamp->name, thischamp->id);
	return (1);
}

int main(void)
{
	t_vm		*vm = ft_memalloc(sizeof(t_vm));
	t_champ		*🅱️hampion = ft_memalloc(sizeof(t_champ));
	t_process	*process = ft_memalloc(sizeof(t_process));
	t_instr		instr;

	if (!vm || !(vm->map = (unsigned char *)ft_memalloc(MEM_SIZE)))
		ERROR("Cannot initiate test");
	vm->map[0] = 1;
	🅱️hampion->id = 1;
	vm->champ = 🅱️hampion;
	ft_strcat(🅱️hampion->name, "tamere");
	instr = instr_params(vm, process);
	inttounsignedchar(1, &vm->map[1]);
	if (!live(instr))
		ERROR("FAIL");
}
