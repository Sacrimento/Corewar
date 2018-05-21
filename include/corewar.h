#ifndef __COREWAR_H__
#define __COREWAR_H__

#include "libft.h"
#include "op.h"

typedef struct  s_champ
{
	int				id;
	int				size;
	int				lives;
	char 			*name;
	char 			*comment;
	struct s_champ	*next;
}				t_champ;

typedef struct  s_process
{
	int					alive;
	int					pc;
	int					carry;
	int					reg[REG_SIZE];
	struct s_process	*next;
}				t_process;

typedef struct 	s_vm
{
	int					opt;
	int					processes_nbr;
	int					cycle;
	unsigned char		*map;
	struct s_champ		*champ;
	struct s_process	*processes;
}				t_vm;

//free.c

int			free_vm(t_vm *vm);

//init_champs.c

t_champs	*init_champs(int ac, char **av);

//error.c

int		usage(void);
int		error_mall(int err);

#endif