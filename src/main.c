/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by abouvero          #+#    #+#             */
/*   Updated: 2018/05/28 13:13:20 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

void 	print_champs(t_champ *champ)
{
	while (champ)
	{
		ft_printf("Id : %d | Size : %d | lives : %d | name : %s | comment : %s\n", champ->id, champ->size, champ->lives, champ->name, champ->comment);
		champ = champ->next;
	}
}

void 	mem_dump(unsigned char *map)
{
	int 	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%4.2x", map[i++]);
		if (!(i % 16) && i != 0)
			ft_putchar('\n');
		else
			ft_putchar(' ');
	}
}

int		main(int argc, char **argv)
{
	t_vm	*vm;
	int 	opt;

	opt = 0; //RM
	//if ((opt = set_opt(argc, argv)) == -1 || check_inputs(argc, argv))
	//	return (1);
	if (!(vm = init_vm(argc, argv, opt)))
		return (free_vm(vm));
	print_champs(vm->champ);
	mem_dump(vm->map);
	free_vm(vm);
	return (0);
}