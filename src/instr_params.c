/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by abouvero          #+#    #+#             */
/*   Updated: 2018/06/05 11:38:51 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

t_param			*decode_param_type(unsigned char ocp)
{
	int cursor;
	t_param *parameters;

	cursor = 0;
	if (!(parameters = (t_param*)ft_memalloc(sizeof(t_param) * 3)))
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
	|| !(parameters = decode_param_type(vm->map[process->pc + 1]))
	|| !parameters[0].type)
	{
		if (!parameters)
		ERROR("incorrect vm");
		return (NULL);
	}
	while (++i < 3 && parameters[i].type != 0)
	{
		parameters[i].value = bytetoint(&vm->map[cursor], parameters[i].type);
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
	t_param *parameters;
	t_instr instr;

	instr = instr_params(vm, process);
	// get_params(vm, process);
	if (vm->map[process->pc] == 1)
		return (live(instr));
	//blablablacode
	ft_memdel((void**)&parameters);
	return (1);
}

int				free_params(t_param **params, int ret)
{
	if (*params)
	{
		free(*params);
		*params = NULL;
	}
	return (ret);
}