#include "corewar.h"

static int  check_champs_length(int argc, char **argv)
{
	//Check si les champs > 0 bytes && < a max_size
	return (0);
}

int			check_inputs(int argc, char **argv)
{
	//Check des defsines d'op.h
	return (0);
}

int 		check_champ_ext(char *name)
{
	int 	len;

	len = ft_strlen(name);
	if (name[len - 1] == 'r' && name[len - 2] == 'o' &&
		name[len - 3] == 'c' && name[len - 4] == '.')
		return (1);
	return (0);
}

char		*get_champ(char *file_name)
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
}

t_champs	*fill_new_champ(t_champs *champ, char *file)
{
	champ->id = 0;
	champ->size = 0;
	champ->lives = 0;
	champ->next = NULL;
	champ->name = get_header(file, 1);
	champ->comment = get_header(file, 2);

	return (champ);
}

t_champs 	*champs_push_fr(t_champs *champ, char *file)
{
	t_champs	*new;

	if (!(new = (t_champs *)ft_memalloc(sizeof(t_champs))))
		return (error_mall());
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
			ft_putstr_fd("Fichier '.cor' attendu\n", 2);
			return (usage()); // 0
		if (!(file = get_champ(av[i])))
			return (NULL);
		if (!(champs = champs_push_fr(champs, file)))
			return (NULL);
	} 
	return (champs);
}

t_vm		init_vm(int argc, char **argv)
{
	t_vm		*vm;
	t_champs	*champs;

	if (!(champs = init_champs(argc, argv) || check_champs_length(champs)))
		return (error_mall()); //Pas forcement malloc
	if (!(vm = (t_vm*)malloc(sizeof(t_vm))))
		return (error_mall());
	if (!(vm->map = (unsigned char *)ft_memalloc(MEM_SIZE - 1)))
		return (error_mall());
	vm->opt = opt;
	load_champs(vm, champs);
}