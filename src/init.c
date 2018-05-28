/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by abouvero          #+#    #+#             */
/*   Updated: 2018/05/25 17:52:39 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int			check_inputs(int argc, char **argv)
{
	//Check des defsines d'op.h
	return (0);
}

static int	list_length(t_champ *champ)
{
	return (champ ? 1 + list_length(champ->next) : 0);
}

void		load_champs(t_vm *vm, int index)
{
	t_champ *ch;
	int 	size;
	int 	i;
	int 	sta;

	sta = 0;
	ch = vm->champ;
	while (ch)
	{
		i = 0;
		size = ch->size;
		while (i < size)
			vm->map[sta + i] = ch->code[i++];
		sta += index;
		ch = ch->next;
	}
}

t_vm		*init_vm(int argc, char **argv, int opt)
{
	t_vm		*vm;
	t_champ		*champs;

	(void)opt; //RM
	champs = NULL;
	if (!(champs = init_champs(argc, argv)))
		return (0); 
	if (!(vm = (t_vm*)ft_memalloc(sizeof(t_vm))))
		return (error_mall(0));
	if (!(vm->map = (unsigned char *)ft_memalloc(MEM_SIZE)))
		return (error_mall(0));
	vm->opt = opt;
	vm->processes_nbr = 0;
	vm->cycle = 0;
	vm->champ = champs;
	vm->processes= NULL;
	load_champs(vm, MEM_SIZE / list_length(vm->champ));
	return (vm);
}