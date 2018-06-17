/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by abouvero          #+#    #+#             */
/*   Updated: 2018/06/17 13:35:12 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

t_param		*decode_param_type(unsigned char ocp)
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
		if ((ocp >> (cursor * 2)) & REG_CODE)
			parameters[2 - iterator].type = T_REG;
		else if ((ocp >> (cursor * 2)) & DIR_CODE)
			parameters[2 - iterator].type = T_DIR;
		else if ((ocp >> (cursor * 2)) & IND_CODE)
			parameters[2 - iterator].type = T_IND;
		iterator++;
	}
	for (int i = 0; i < 3; i++)
		ft_printf("OCP : PARAM%d : %d\n", i, parameters[i].type);
	return (parameters);
}

t_param		*get_params(t_vm *vm, t_process *process, int opcode)
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
		//ERROR("get_params for instructions : cannot decode parameter(s) type");
		return (NULL);
	}
	while (++i < 3 && parameters[i].type != 0)
	{
		parameters[i].value = byte_to_int(vm->map, cursor,
		type_to_size(parameters[i].type, opcode));
		cursor += type_to_size(parameters[i].type, opcode);
	}
	return (parameters);
}

t_instr		instr_params(t_vm *vm, t_process *process, int opc)
{
	t_instr instr;

	instr.vm = vm;
	instr.process = process;
	instr.params = NULL;
	instr.opcode = opc;
	return (instr);
}

int			decal_pc(t_instr instr, int decal, int ret)
{
	//static int i = 0;
	ft_printf("opcode:%d\n", instr.opcode);
	ft_printf("actual process:%d\n", instr.process->pc);
	if (instr.opcode - 1 < 17 && ret == 0)
		ft_printf("{RED}INSTRUCTION FAILED %s{EOC}\n", g_op_tab[instr.opcode - 1].name);
	if (instr.opcode - 1 < 17 && ret == 1)
		ft_printf("{GREEN}INSTRUCTION SUCCEED %s{EOC}\n", g_op_tab[instr.opcode - 1].name);
	ft_printf("ADV %d (%#.4x -> ", decal, instr.process->pc);
	instr.process->pc = (instr.process->pc + decal) % MEM_SIZE;
	ft_printf("%#.4x) ", instr.process->pc);
	while (decal > 0)
		ft_printf("%.2x ", instr.vm->map[instr.process->pc - decal--]);
	ft_printf("\n");
	instr.process->cycles_left = -1;
	//ft_printf("{YELLOW}i:%d|process:%s|carry=%d{EOC}\n",
	//i++,
	//g_op_tab[instr.opcode - 1].name, instr.process->carry);
/* 	if (instr.vm->processes_nbr >= 15)
		usleep(900000); */
	return (ret);
}

int			free_params(t_instr instr, int ret)
{
	int to_decal;
	int cursor;

	cursor = -1;
	to_decal = 2;
	if (instr.params)
	{
		while (++cursor < 3)
			to_decal += type_to_size(instr.params[cursor].type, instr.opcode);
		decal_pc(instr, to_decal, ret);
		free(instr.params);
	}
	return (ret);
}
