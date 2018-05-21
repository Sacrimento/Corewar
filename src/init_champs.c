/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_champs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:32:13 by abouvero          #+#    #+#             */
/*   Updated: 2018/05/21 13:12:01 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int 		check_champ_ext(char *name)
{
	int 	len;

	len = ft_strlen(name);
	if (name[len - 1] == 'r' && name[len - 2] == 'o' &&
		name[len - 3] == 'c' && name[len - 4] == '.')
		return (1);
	return (0);
}

char			*get_header(char *file, int nc)
{
	
}

static char		*get_champ(char *file_name)
{
	int 	fd;
	int 	ret;
	char	*content;

	content = NULL;
	if (!(fd = open(file_name, O_RDONLY)))
		return (NULL);
	ret = get_next_line(fd, &content);
	if (ret == 0 || ret == -1)
	{
		ft_putstr_fd("Le champion ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(" est vide ou invalide\n", 2);
		return (NULL);
	}
	return (content);
}

static t_champs	*fill_new_champ(t_champs *champ, char *file)
{
	champ->id = 0;
	champ->size = 0;
	champ->lives = 0;
	champ->next = NULL;
	champ->name = get_header(file, 1);
	champ->comment = get_header(file, 2);
	ft_memdel((void**)&file);

	return (champ);
}

static t_champs *champs_push_fr(t_champs *champ, char *file)
{
	t_champs	*new;

	if (!(new = (t_champs *)ft_memalloc(sizeof(t_champs))))
		return (error_mall(0));
	new = fill_new_champ(new, file);
	if (!champ)
		return (new);
	new->id = champ->id + 1;
	new->next = champ;
	return (new);
}

t_champs	*init_champs(int ac, char **av)
{
	int 		i;
	char		*file;
	t_champs	*champs;

	i = -1;
	file = NULL;
	champs = NULL;
	while (++i < ac)
	{
		if (*av[i] == '-' && i + 1 < ac)
			i++;
		if (!check_champ_ext(av[i]))
			ft_putstr_fd(av[i], 2);
			ft_putstr_fd(" : fichier '.cor' attendu\n", 2);
			return (usage()); // 0
		if (!(file = get_champ(av[i])))
			return (NULL);
		if (!(champs = champs_push_fr(champs, file)))
			return (NULL);
	} 
	return (champs);
}