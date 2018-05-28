/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by abouvero          #+#    #+#             */
/*   Updated: 2018/05/28 16:53:51 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

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

int		usage(void)
{
	ft_putstr_fd("Coucou c'est l'usage\n", 2);
	return (0);
}
