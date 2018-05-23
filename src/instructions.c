/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:36:15 by mfonteni          #+#    #+#             */
/*   Updated: 2018/05/23 14:17:36 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO: fonction qui dechiffre l'encodage des parametres
#include "../include/corewar.h"

int live(t_champ *champ_list, int champ_num, int display_flag)
{
	t_champ *champ;

	if (!champ_list)
		return (0);
	if (!(champ = get_champ_by_num(champ_list, champ_num)))
		return (0);
	champ->lives++;
	he_lives(champ, display_flag);
	return (1);
}
//not sure about this one :
int ld(t_process *process, int value, int *reg)
{
	if (!reg)
		return (process->carry = 0);
	*reg = value;
	return (process->carry = 1);
}

int lld()
{
	
}

int st(t_process *process, int *reg1, int *reg2)
{
	if (!reg1 || !reg2)
		return (process->carry = 0);
	*reg2 = *reg1;
	return (process->carry = 1);
}

int sti()
{

}
//Elle prendra un index, et fait un saut à cette adresse si le carry est à 1.
//TODO: What do they mean by "jump" ? Do we have to move the PC ?
int zjmp()
{
	
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

int aff(int *reg)
{
	if (!reg)
		return (0);
	ft_putchar(*reg % 256);
	return (1);
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