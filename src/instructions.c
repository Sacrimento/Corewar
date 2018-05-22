/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:36:15 by mfonteni          #+#    #+#             */
/*   Updated: 2018/05/22 13:39:34 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//fonction qui dechiffre l'encodage des parametres
#include "../include/corewar.h"

int live(t_champ *champ_list, int champ_num)
{
	t_champ *champ;

	if (!champ_list)
		return (0);
	if (!(champ = get_champ_by_num(champ_list, champ_num)))
		return (0);
	champ->lives++;
}

int ld(t_process *process, unsigned char value, unsigned char *reg)
{
	if (!reg)
		return (process->carry = 0);
	
}