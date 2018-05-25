/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by abouvero          #+#    #+#             */
/*   Updated: 2018/05/25 17:36:28 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void 	mem_dump(unsigned char *map)
{
	int 	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 16 && i != 0)
			ft_putchar('\n');
		else if (i % 8 && i != 0)
			ft_putchar(' ');
		ft_printf("%x ", map[i++]);
	}
}

int		main(int argc, char **argv)
{
	t_vm	*vm;
	int 	opt;

	if ((opt = set_opt(argc, argv)) == -1 || check_inputs(argc, argv))
		return (1);
	if (!(vm = init_vm(argc, argv, opt)))
		return (free_vm(vm));
	mem_dump(vm->map);
	free_vm(vm);
	return (0);
}