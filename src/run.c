/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 11:22:38 by abouvero          #+#    #+#             */
/*   Updated: 2018/06/19 15:34:58 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

static void	init_instr_tab(t_vm *vm)
{
	vm->instr_tab[0] = &live;
	vm->instr_tab[1] = &ld;
	vm->instr_tab[2] = &st;
	vm->instr_tab[3] = &add;
	vm->instr_tab[4] = &sub;
	vm->instr_tab[5] = &and;
	vm->instr_tab[6] = &or;
	vm->instr_tab[7] = &xor;
	vm->instr_tab[8] = &zjmp;
	vm->instr_tab[9] = &ldi;
	vm->instr_tab[10] = &sti;
	vm->instr_tab[11] = &core_fork;
	vm->instr_tab[12] = &lld;
	vm->instr_tab[13] = &lldi;
	vm->instr_tab[14] = &core_lfork;
	vm->instr_tab[15] = &aff;
}

static int	exec_process(t_process *process, t_vm *vm)
{
	unsigned char	opc;

	if (!process)
		return (0);
	while (process)
	{
		if (process->cycles_left > 1)
			process->cycles_left--;
		else
		{
			opc = vm->map[process->pc % MEM_SIZE];
			if (opc < 1 || opc > 16)
				return (decal_pc((instr_params(vm, process, opc)), 1, 0));
			if (process->cycles_left == -1)
			{
				process->cycles_left = g_op_tab[opc - 1].nb_cycle - 1;
				return (0);
			}
			//ft_printf("OCP : %d\n", opc);
			//ft_printf("{MAGENTA}PROCESS %d {EOC}\n", process->id);
			if (process->id == 2)
				ft_printf("Process %d execs %s\n", process->id, g_op_tab[opc -1].name);
			vm->instr_tab[opc - 1](instr_params(vm, process, opc));
			//ft_printf("NEW PC : %d\n", process->pc);
		}
		process = process->next;
	}
	return (1);
}

static int	mem_dump(unsigned char *map)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%.2x", map[i++]);
		if (!(i % 32) && i != 0)
			ft_putchar('\n');
		else
			ft_putchar(' ');
	}
	return (1);
}

static void	check_vm(t_vm *vm, int *check, int *ctd)
{
	t_champ *ch;

	ch = vm->champ;
	//INFO("CHECKS");
	check_process(vm);
	if (*check == MAX_CHECKS || vm->lives >= NBR_LIVE)
	{
		*check = 0;
		*ctd -= CYCLE_DELTA;
		ft_printf("Cycle to die is now %d\n", *ctd);
	}
	vm->cycle = 0;
	vm->lives = 0;
	*check += 1;
	while (ch)
	{
		ch->lives = 0;
		ch = ch->next;
	}
}

int			run(t_vm *vm)
{
	int		ctd;
	int		check;

	check = 0;
	init_instr_tab(vm);
	ctd = CYCLE_TO_DIE;
	while (vm->processes_nbr && ctd > 0)
	{
		ft_printf("It is now cycle %d\n", vm->tt_cycle);
		if (vm->cycle == ctd)
			check_vm(vm, &check, &ctd);
		exec_process(vm->processes, vm);
		if (vm->tt_cycle == vm->dump)
			return (mem_dump(vm->map));
		vm->cycle++;
		vm->tt_cycle++;
		ft_printf("{CYAN}processes nb:%d{EOC}\n", vm->processes_nbr);
	}
	return (1);
}
