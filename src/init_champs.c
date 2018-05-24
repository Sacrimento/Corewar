/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_champs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:32:13 by abouvero          #+#    #+#             */
/*   Updated: 2018/05/24 15:14:21 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

static int 		check_champ_ext(char *name)
{
	int 	len;

	len = ft_strlen(name);
	if (name[len - 1] == 'r' && name[len - 2] == 'o' &&
		name[len - 3] == 'c' && name[len - 4] == '.')
		return (1);
	return (0);
}

int				get_champ_len(char *fn)
{
	int		fd;
	int		ret;
	char	buff;
	int		len;

	len = 0;
	if (!(fd = open(fn, O_RDONLY)))
		return (-1);
	while ((ret = read(fd, buff, 1)))
		len++;
	close(fd);

	return (len);
}

char			*get_name(unsigned char *file)
{
	int		*
}

char			*get_header(char *file, int nc)
{
	unsigned char	buff;
	int				ret;

}

static char		*get_champ(char *file_name)
{
	int 			fd;
	int 			ret;
	unsigned char	*content;
	int				len;
	int				i;

	i = 0;
	if ((len = get_champ_len(file_name)) == -1)
		return (NULL);
	content = NULL;
	if (!(content = (unsigned char *)ft_memalloc(sizeof(char) * (len + 1))))
		return (error_mall(0));
	if (!(fd = open(file_name, O_RDONLY)))
		return (NULL);
	while (read(fd, content[i++], 1));
	content[i] = '\0';
	close(fd);
	return (content);
}

static t_champ	*fill_new_champ(t_champ *champ, unsigned char *file)
{
	champ->id = 0;
	champ->size = 0;
	champ->lives = 0;
	champ->next = NULL;
	if (!(champ->name = get_name(file)))
		return (NULL);
	if (!(champ->comment = get_comment(file)))
		return (NULL);
	champ->code = get_code(file);
	return (champ);
}

static t_champ *champs_push_fr(t_champ *champ, unsigned char *file)
{
	t_champ	*new;

	if (!(new = (t_champ *)ft_memalloc(sizeof(t_champ))))
	{
		error_mall(0);
		return (NULL);
	}
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
	unsigned char		*file;
	t_champ			*champs;

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
		ft_memdel((void**)&file);
	} 
	return (champs);
}