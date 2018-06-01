/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by abouvero          #+#    #+#             */
/*   Updated: 2018/06/01 18:08:20 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

// static int			check_inputs(void)
// {
// 	//Check des defsines d'op.h
// 	return (0);
// }


void				mem_dump(unsigned char *map)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%2.2x", map[i++]);
		if (!(i % 32) && i != 0)
			ft_putchar('\n');
		else
			ft_putchar(' ');
	}
}

int					main(int argc, char **argv)
{
	t_vm	*vm;

	//if ((opt = set_opt(argc, argv)) == -1 || check_inputs(argc, argv))
	//	return (1);
	if (!(vm = init_vm(argc, argv)))
		return (1);
	continue_process(vm, vm->processes);
	//mem_dump(vm->map);
	free_vm(vm);
	return (0);
}
