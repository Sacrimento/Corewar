/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by abouvero          #+#    #+#             */
/*   Updated: 2018/06/01 17:47:49 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int		check_num(t_champ *ch, int num, int env)
{
	while (ch)
	{
		if (ch->id == 0 && env)
		{
			if (ch->next)
				ch = ch->next;
			else
				break ;
		}
		if (ch->id == num)
			return (0);
		ch = ch->next;
	}
	return (1);
}

int		error_mall(int err)
{
	ft_putstr_fd("Erreur d'allocation memoire\n", 2);
	return (err);
}

t_champ	*error_file(char *str, char *file, t_champ *champ)
{
	rec_free_champs(champ);
	return (ft_printf(str, file) ? NULL : 0);
}

int		usage(int ret)
{
	ft_printf("usage : ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...\n");
	return (ret);
}

int 	illegal_opt(char *opt, int ret)
{
	ft_printf("Illegal option : %s\n", opt);
	return (usage(ret));
}
