/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by abouvero          #+#    #+#             */
/*   Updated: 2018/06/12 12:51:33 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

t_param			*decode_param_type(unsigned char ocp)
{
	int cursor;
	int iterator;
	t_param *parameters;

	cursor = 0;
	iterator = 0;
	if (!(parameters = (t_param*)ft_memalloc(sizeof(t_param) * 3)))
		return (NULL);
	while (++cursor < 4)
	{
		if ((ocp << (cursor * 2)) & 0x0000000F)
			parameters[iterator].type = T_REG;
		else if ((ocp << (cursor * 2)) & 0x000000F0)
			parameters[iterator].type = T_DIR;
		else if ((ocp << (cursor * 2)) & 0x000000FF)
			parameters[iterator].type = T_IND;
		iterator++;
	}
	return (parameters);
}

t_param			*get_params(t_vm *vm, t_process *process)
{
	t_param	*parameters;
	int		i;
	int		cursor;

	i = -1;
	cursor = process->pc + 2;
	parameters = NULL;
	if (!vm || !vm->map || !process
	|| !(parameters = decode_param_type(vm->map[(process->pc + 1) % MEM_SIZE]))
	|| !parameters[0].type)
	{
		ERROR("get_params for instructions : cannot decode parameter(s) type");
		return (NULL);
	}
	while (++i < 3 && parameters[i].type != 0)
	{
		parameters[i].value = bytetoint(vm->map, cursor, parameters[i].type);
		cursor += type_to_size(parameters[i].type);
	}
	return (parameters);
}

t_instr			instr_params(t_vm *vm, t_process *process)
{
	t_instr instr;

	instr.vm = vm;
	instr.process = process;
	instr.params = NULL;
	return (instr);
}

int			decal_pc(t_process *process, int decal, int ret)
{
	process->pc = (process->pc + decal) % MEM_SIZE;
	process->cycles_left = -1;
	return (ret);
}

int				free_params(t_instr instr, int ret)
{
	int to_decal;
	int cursor;

	cursor = -1;
	to_decal = 0;
	if (!ret)
		ERROR("INSTRUCTION FAILED");
	if (instr.params)
	{
		while (++cursor < 3)
			to_decal += type_to_size(instr.params[cursor].type);
		decal_pc(instr.process, to_decal, 1);
		free(instr.params);
	}
	return (ret);
}
