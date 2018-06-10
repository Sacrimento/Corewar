/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by abouvero          #+#    #+#             */
/*   Updated: 2018/06/10 13:12:32 by abouvero         ###   ########.fr       */
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
		if ((ocp >> (cursor * 2)) & 0x0000000F)
			parameters[iterator].type = T_REG;
		else if ((ocp >> (cursor * 2)) & 0x000000F0)
			parameters[iterator].type = T_IND;
		else if ((ocp >> (cursor * 2)) & 0x000000FF)
			parameters[iterator].type = T_DIR;
		iterator++;
	}
	INFONUM(ocp);
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
		return (NULL);
	while (++i < 3 && parameters[i].type != 0)
	{
		parameters[i].value =
		bytetoint(vm->map, cursor, parameters[i].type);
		cursor += parameters[i].type;
	}
	process->pc = cursor;
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

int				continue_process(t_vm *vm, t_process *process)
{
	t_instr instr;

	instr = instr_params(vm, process);
	// get_params(vm, process);
	if (vm->map[process->pc % MEM_SIZE] == 1)
		return (live(instr));
	//blablablacode
	return (1);
}

int			decal_pc(t_process *process, int decal, int ret)
{
	process->pc = (process->pc + decal) % MEM_SIZE;
	process->cycles_left = -1;
	return (ret);
}

int				free_params(t_instr instr, int ret)
{
	if (instr.params)
	{
		decal_pc(instr.process,
		instr.params[0].type
		+ instr.params[1].type
		+ instr.params[2].type, 1);
		free(instr.params);
		instr.params = NULL;
	}
	return (ret);
}