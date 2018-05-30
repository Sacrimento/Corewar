/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:36:15 by mfonteni          #+#    #+#             */
/*   Updated: 2018/05/30 17:07:59 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Toi qui passe sur ce fichier, rien n'est definitif pour l'instant,
 * j'experimente pour chercher a comprendre certains points qui sont encore
 * flous dans ma tete, la structure de données est susceptible de changer
 * encore un peu, mais l'idée est la.
 * 
 * Glosssaire :
 * OCP = Octet de Codage des Parametres
 * ***********************************************************
 * TODO: 
 * - Define a defnitive data structure for instructions
 *
*/

#include "../include/corewar.h"

t_param	*decode_param_type(t_vm *vm, unsigned char ocp)
{
	int cursor;
	t_param *parameters;

	cursor = 0;
	parameters = ft_memalloc(sizeof(t_param) * 3);
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

int		decode_OCP(t_vm *vm, unsigned char byte, int i)
{
	int cursor;

	decode_param_type(instr, vm, byte, 0);
	while (++i < 4)
	{
		if ((cursor = instr->process->pc + i) && (byte >> (i * 2)) & 0x0000000F)
		{
			if (vm->map[cursor] > REG_NUMBER)
				return (0);
			instr->params[i].value = instr->process->reg[vm->map[cursor]];
			instr->params[i].address = &instr->process->reg[vm->map[cursor]];
		}
		else if ((byte >> (i * 2)) & 0x000000F0)
		{
			instr->params[i].value = vm->map[cursor];
			instr->params[i].address = &vm->map[cursor];
		}
		else if ((byte >> (i * 2)) & 0x000000FF)
		{
			instr->params[i].value = vm->map[vm->map[cursor] % MEM_SIZE];
			instr->params[i].address = &vm->map[vm->map[cursor] % MEM_SIZE];
		}
	}
	return (1);
}

int		live(t_instr *instr, t_champ *champions, t_vm *vm)
{
	t_champ *thischamp;

	if (!vm || !champions
	|| !(thischamp = get_champ_by_num(champions, (instr->params[1]).value)))
		return (0);
	thischamp->lives++;
	ft_printf("[%d]{BLUE}Champion %s(id:%d) is alive{EOC}",
		thischamp->lives, thischamp->name, thischamp->id);
	return (1);
}
//not sure about this one :
int		ld(t_instr *instr, t_champ *champions, t_vm *vm)
{
	if ((instr->params[1]).type != REG_CODE)
		return (-1);
	if (!((instr->params[0]).type == IND_CODE
	|| (instr->params[0]).type == DIR_CODE)
	|| (instr->params[0]).value == 0)
		return (instr->process->carry = 0);
	if ((instr->params[0]).type == IND_CODE)
		*(int*)(instr->params[1]).address
		= vm->map[((instr->params[0]).value % IDX_MOD) % MEM_SIZE];
	else
		*(int*)(instr->params[1]).address = (instr->params[0]).value;
	return (instr->process->carry = 1);
}

int lld(t_instr *instr, t_champ *champions, t_vm *vm)
{
	if ((instr->params[1]).type != REG_CODE
	|| !((instr->params[0]).type == IND_CODE
	|| (instr->params[0]).type == DIR_CODE))
		return (-1);
	if ((instr->params[0]).value == 0)
		return (instr->process->carry = 0);
	if ((instr->params[0]).type == IND_CODE)
		*(int*)(instr->params[1]).address
		= vm->map[(instr->params[0]).value % MEM_SIZE];
	else
		*(int*)(instr->params[1]).address = (instr->params[0]).value;
	return (instr->process->carry = 1);
}

int st(t_instr *instr, t_champ *champions, t_vm *vm)
{
	if ((instr->params[0])->type != T_REG)
		return (process->carry = 0);
	*reg2 = *reg1;
	return (process->carry = 1);
}

int sti()
{

}

int zjmp(t_process *process, unsigned char *addr)
{
	if (!process || process->carry == 0)
		return (0);
}

// prend 2 index et 1 registre, additionne les 2 premiers, 
// traite ca comme une adresse, y lit une valeur de la taille d’un 
// registre et la met dans le 3eme.
int ldi()
{

}

int lldi()
{
	
}

int aff(t_instr *instr, t_champ *champions, t_vm *vm)
{
	if ((instr->params[0]).value > REG_NUMBER || !(instr->params[0]).is_reg)
		return (instr->process->carry = 0);
	//check if !char is the same NUL from the subject
	if (!instr->process->reg[(instr->params[0]).value])
		return (instr->process->carry = 1);
	ft_printf("%s", instr->process->reg[(instr->params[0]).value] % 256);
	return (instr->process->carry = 0);
}

int fork()
{

}

int lfork()
{
	
}

int st()
{
	
}