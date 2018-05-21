#ifndef __COREWAR_H__
#define __COREWAR_H__

#include "libft.h"
#include "op.h"

/*
* ERROR HANDLING DEFINES
*/

#define MALLOC_ERR		1
#define CHAMP_LEN_ERR	2
#define OPT_ERR			3

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
	struct s_process	*next;
}				t_process;

typedef struct 	s_vm
{
	int				opt;
	int				processes;
	int				cycle;
	unsigned char	*map;
	struct s_champ	*champ;
}				t_vm;

#endif