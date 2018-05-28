/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_champs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:32:13 by abouvero          #+#    #+#             */
/*   Updated: 2018/05/28 13:22:27 by abouvero         ###   ########.fr       */
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
	if (!(parse_champ(file, champ)))
		return (NULL);
	return (champ);
}

static t_champ *champs_push_fr(t_champ *champ, char *file)
{
	t_champ	*new;

	if (!(new = (t_champ *)ft_memalloc(sizeof(t_champ))))
	{
		error_mall(0);
		return (NULL);
	}
	if (!(new = fill_new_champ(new, file)))
		return (NULL);
	if (!champ)
		return (new);
	new->id = champ->id + 1;
	new->next = champ;
	return (new);
}

t_champ			*init_champs(int ac, char **av)
{
	int 				i;
	t_champ				*champs;

	i = 0;
	champs = NULL;
	while (++i < ac)
	{
		if (*av[i] == '-' && i + 1 < ac)
			i++;
		if (!check_champ_ext(av[i]))
		{
			ft_printf("%s : fichier '.cor' attendu\n", av[i]);
			usage();
			return (NULL);
		}
		if (!(champs = champs_push_fr(champs, av[i])))
			return (NULL);
	} 
	return (champs);
}