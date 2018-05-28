/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_champs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:32:13 by abouvero          #+#    #+#             */
/*   Updated: 2018/05/25 17:52:33 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

static int 		check_champ_ext(char *name)
{
	int 	len;

	len = ft_strlen(name);
	if (len > 4 && name[len - 1] == 'r' && name[len - 2] == 'o' &&
					name[len - 3] == 'c' && name[len - 4] == '.')
		return (1);
	return (0);
}

static t_champ	*fill_new_champ(t_champ *champ, char *file)
{
	champ->id = 0;
	champ->size = 0;
	champ->lives = 0;
	champ->next = NULL;
	parse_champ(champ, file);
	return (champ);
}

static t_champ *champs_push_fr(t_champ *champ, char *file)
{
	t_champ	*new;

	if (!(new = (t_champ *)ft_memalloc(sizeof(t_champ))))
		return (error_mall(0));
	new = fill_new_champ(new, file);
	if (!champ)
		return (new);
	new->id = champ->id + 1;
	new->next = champ;
	return (new);
}

t_champ	*init_champs(int ac, char **av)
{
	int 				i;
	t_champ				*champs;

	i = -1;
	champs = NULL;
	while (++i < ac)
	{
		if (*av[i] == '-' && i + 1 < ac)
			i++;
		if (!check_champ_ext(av[i]))
			ft_putstr_fd(av[i], 2);
			ft_putstr_fd(" : fichier '.cor' attendu\n", 2);
			return (usage());
		if (!(champs = champs_push_fr(champs, av[i])))
			return (NULL);
	} 
	return (champs);
}