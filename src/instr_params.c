/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by abouvero          #+#    #+#             */
/*   Updated: 2018/05/31 14:45:53 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

t_param		*decode_param_type(t_vm *vm, unsigned char ocp)
{
	int cursor;
	t_param *parameters;

	cursor = 0;
	if (!(parameters = ft_memalloc(sizeof(t_param) * 3)))
		return (NULL);
	while (++cursor < 4)
	{
		if ((ocp >> (cursor * 2)) & 0x0000000F)
			parameters[cursor].type = T_REG;
		else if ((ocp >> (cursor * 2)) & 0x000000F0)
			parameters[cursor].type = T_IND;
		else if ((ocp >> (cursor * 2)) & 0x000000FF)
			parameters[cursor].type = T_DIR;
	}
	return (parameters);
}

static int	bytetoint(unsigned char *ram, int ammount_of_bytes)
{
	if (ammount_of_bytes == 1)
		return (ram[0]);
	if (ammount_of_bytes == 2)
		return (ram[0] | (ram[1] << 8));
	if (ammount_of_bytes == 4)
		return ((ram[0] << 24) | (ram[1] << 16) | (ram[2] << 8) | ram[3]);
	return (0);
}

t_param		*get_params(t_vm *vm, t_process *process)
{
	t_param	*parameters;
	int		iterator;
	int		cursor;

	iterator = -1;
	cursor = process->pc + 2;
	if (!(parameters = decode_param_type(vm, vm->map[process->pc]))
	|| (parameters[0]).type == 0)
		return (NULL);
	while (++iterator < 3 && parameters[iterator].type != 0)
	{
		parameters[iterator].value
		= bytetoint(&vm->map[cursor], parameters[iterator].type);
		cursor += parameters[iterator].type;
	}
	return (parameters);
}

int		continue_process(t_vm *vm, t_process *process)
{
	t_param *parameters;

	if (!(parameters = get_params(vm, process)))
		return (0);
	//blablablacode
	ft_memdel((void**)&parameters);
	return (1);
}