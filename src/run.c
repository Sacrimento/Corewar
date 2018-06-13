/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 11:22:38 by abouvero          #+#    #+#             */
/*   Updated: 2018/06/13 13:53:48 by abouvero         ###   ########.fr       */
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

	opc = vm->map[process->pc % MEM_SIZE];
	if (process->cycles_left == -1)
	{
		process->cycles_left = g_op_tab[opc - 1].nb_cycle - 1;
		return (0);
	}
	if (opc < 1 || opc > 16)
		return (decal_pc(process, 1, 0));
	ft_printf("OCP : %d\n", opc);
	vm->instr_tab[opc - 1](instr_params(vm, process, opc));
	ft_printf("NEW PC : %d\n", process->pc);
	return (1);
}

int	mem_dump(unsigned char *map)
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

static void	exec_processes(t_process *process, t_vm *vm)
{
	if (!process)
		return ;
	while (process)
	{
		if (process->cycles_left > 1)
			process->cycles_left--;
		else
			exec_process(process, vm);
		process = process->next;
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
		ft_printf("CYCLE : %d\n", vm->cycle);
		if (!(vm->cycle % ctd) && vm->cycle)
		{
			check_process(vm);
			if (++check == MAX_CHECKS || vm->lives >= NBR_LIVE)
			{
				vm->lives = 0;
				check = 0;
				ctd -= CYCLE_DELTA;
			}
		}
		exec_processes(vm->processes, vm);
		if (vm->cycle == vm->dump - 1)
			return (mem_dump(vm->map));
		vm->cycle++;
	}
	return (1);
}
