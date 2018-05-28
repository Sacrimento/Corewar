/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by abouvero          #+#    #+#             */
/*   Updated: 2018/05/28 14:33:46 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int			check_inputs(void)
{
	//Check des defsines d'op.h
	return (0);
}

static void	introduce_champs(t_champ *champs)
{
	ft_printf("Introducing contestants...\n");
	while (champs)
	{
		ft_printf("* Player %d, weighing %d bytes, ", champs->id, champs->size);
		ft_printf("\"%s\" (\"%s\") !\n", champs->name, champs->comment);
		champs = champs->next;
	}
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
		i = -1;
		size = ch->size;
		while (++i < size)
			vm->map[sta + i] = ch->code[i];
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
	if (!(vm = (t_vm*)ft_memalloc(sizeof(t_vm))) || !(vm->map = (unsigned char *)ft_memalloc(MEM_SIZE)))
	{
		error_mall(0);
		return (NULL);
	}
	vm->opt = opt;
	vm->processes_nbr = 0;
	vm->cycle = 0;
	vm->champ = champs;
	vm->processes= NULL;
	load_champs(vm, MEM_SIZE / list_length(vm->champ));
	introduce_champs(vm->champ);
	return (vm);
}