/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by mfonteni          #+#    #+#             */
/*   Updated: 2018/06/04 17:47:50 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
#define COREWAR_H

#include "../libft/includes/libft.h"
#include "op.h"
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

/********************DEBUG KINGDOM*********************/
#define ERROR(message) ft_printf("{RED}%s{EOC}\n", message)
#define SUCCESS(message) ft_printf("{GREEN}%s{EOC}\n", message)
#define INFO(message) ft_printf("{BLUE}%s{EOC}\n", message)
#define INFONUM(message) ft_printf("{BLUE}%d{EOC}\n", message)
/******************************************************/

typedef struct			s_champ
{
	int					id;
	int					size;
	unsigned int		lives;
	char 				name[PROG_NAME_LENGTH + 1];
	char 				comment[COMMENT_LENGTH + 1];
	unsigned char		*code;
	struct s_champ		*next;
}						t_champ;

typedef struct			s_process
{
	int					alive;
	int					pc;
	int					carry;
	int					reg[REG_NUMBER];
	int					cycles_left;
	struct s_process	*next;
}						t_process;

typedef struct			s_vm
{
	unsigned int		lives;
	int 				last;
	int					dump;
	int					processes_nbr;
	int					cycle;
	unsigned char		*map;
	struct s_champ		*champ;
	struct s_process	*processes;
}						t_vm;

typedef struct			s_param
{
	int					value;
	int					type;
}						t_param;

typedef struct			s_instr
{
	t_vm				*vm;
	t_process			*process;
	t_param				*params;
}						t_instr;

//run.c
int 					run(t_vm *vm);

//free.c
t_vm					*free_vm(t_vm *vm);
t_champ					*rec_free_champs(t_champ *champs);

//init_champs.c
int						init_champs(int ac, char **av, t_vm *vm);

//init.c
t_vm					*init_vm(int argc, char **argv);
int						sort_champs(t_vm *vm);

//get_champ.c
t_champ					*parse_champ(char *file_name , t_champ *champ);
int						fill_id_champs(t_vm *vm);

//error.c
int						usage(int ret);
t_champ					*error_file(char *str, char *file, t_champ *champ);
int						error_mall(int err);
int 					illegal_opt(char *opt, int ret);
int						check_num(t_champ *ch, int num, int env);

//getters.c
t_champ					*get_champ_by_num(t_champ *list, unsigned int num);

//process.c
int						add_process(t_vm *vm, int pc, int id);
void					search_and_destroy_process(t_vm *vm);
int						check_processes(t_process *pro);

//option.c
int						opt(char **av, int ac, int *i, t_vm *vm);

//instr_params.c
t_param					*decode_param_type(unsigned char ocp);
t_param					*get_params(t_vm *vm, t_process *process);
t_instr					instr_params(t_vm *vm, t_process *process);
int						continue_process(t_vm *vm, t_process *process);

//instr_params_checks.c
int						compare_params(t_param *params, int opcode);

//instructions.c
int						continue_process(t_vm *vm, t_process *process);
unsigned int 			bytetoint(unsigned char *ram, int ammount_of_bytes);
int						live(t_instr instr);
int						ld(t_instr instr);
int						lld(t_instr instr);
int						st(t_instr instr);
int						inttobytes(unsigned int n, unsigned char *map);
int						free_params(t_param **params, int ret);


#endif