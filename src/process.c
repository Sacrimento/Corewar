/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 15:22:38 by abouvero          #+#    #+#             */
/*   Updated: 2018/06/01 13:13:30 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

static void	del_process(t_vm *vm, t_process *del)
{
	t_process	*prev;
	t_process	*curr;

	curr = vm->process;
	prev = curr;
	if (!curr)
		return ;
	vm->processes_nbr--;
	if (curr == del)
	{
		vm->process = beg->next;
		ft_memdel((void**)&del);
	}
	curr = curr->next;
	while (curr)
	{
		if (curr == del)
		{
			prev->next = curr->next;
			ft_memdel((void**)&curr);
			return ;
		}
		curr = curr->next;
	}
}

int			check_processes(t_process *pro)
{
	if (!pro)
		return (0);
	while (pro)
	{
		if (pro->alive)
			return (1);
		pro = pro->next;
	}
	return (0);
}

void		search_and_destroy_process(t_vm *vm)
{
	t_process *process;

	process = vm->process;
	if (!process)
		return ;
	while (process)
	{
		if (!process->alive)
			del_process(vm, process);
		process->alive = 0;
		process = process->next;
	}
}

int			add_process(t_vm *vm, int pc, int id)
{
	t_process	*pro;
	t_process	*new;

	pro = vm->processes;
	if (!(new = (t_process*)ft_memalloc(sizeof(t_process))))
		return (error_mall(0));
	new->alive = 1;
	new->pc = pc;
	new->carry = 0;
	new->cycles_left = 0;
	bzero((void *)new->reg, sizeof(new->reg));
	new->reg[0] = id;
	new->next = pro;
	vm->processes_nbr += 1;
	vm->processes = new;
	return (1);
}