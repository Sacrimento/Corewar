/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by mfonteni          #+#    #+#             */
/*   Updated: 2018/06/26 16:15:33 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
#define COREWAR_H

#include "../libft/includes/libft.h"
#include "op.h"
#include <ncurses.h>
#include <fcntl.h>

/********************DEBUG KINGDOM*********************/
#define FD open("/dev/ttys005", O_RDWR)
#define ERROR(message) ft_dprintf(FD, "{RED}%s{EOC}\n", message)
#define SUCCESS(message) ft_dprintf(FD, "{GREEN}%s{EOC}\n", message)
#define INFO(message) ft_dprintf(FD, "{BLUE}%s{EOC}\n", message)
#define INFONUM(message) ft_dprintf(FD, "{BLUE}%d{EOC}\n", message)
/******************************************************/

# define STATS_W		48
# define ARENA_W		197
# define HEADER_W		(ARENA_W + STATS_W)
# define HEADER_H		7
# define HEADER_LINE_1		"   ______                                  "
# define HEADER_LINE_2		"  / ____/___  ________ _      ______ ______"
# define HEADER_LINE_3		" / /   / __ \\/ ___/ _ \\ | /| / / __ `/ ___/"
# define HEADER_LINE_4	"/ /___/ /_/ / /  /  __/ |/ |/ / /_/ / /    "
# define HEADER_LINE_5		"\\____/\\____/_/   \\___/|__/|__/\\____/_/     "

typedef struct			s_champ
{
	int					id;
	int					color;
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
	int					color;
	int					pc;
	int					carry;
	int					reg[REG_NUMBER];
	int					cycles_left;
	struct s_process	*next;
}						t_process;

typedef struct			s_param
{
	int					value;
	int					type;
}						t_param;

typedef struct			s_instr
{
	struct s_vm			*vm;
	t_process			*process;
	t_param				params[3];
	int					opcode;
}						t_instr;

typedef struct			s_vm
{
	unsigned int		lives;
	t_champ				*last;
	int					dump;
	int					processes_nbr;
	int					cycle;
	int					tt_cycle;
	int					visu;
	unsigned char		*map;
	char				*colors_map;
	int 				(*instr_tab[16])(t_instr);
	struct s_champ		*champ;
	struct s_process	*processes;
	int					ctd;
}						t_vm;

typedef struct			s_visu
{
	int					slow;
	int					ch;
	int					*pc;
	int					pcx;
	int					pcy;
	int					start;
	int					pos;
	int					ind;
	WINDOW  			*win;
	WINDOW  			*score;
}						t_visu;

//visu
WINDOW	*init_visu();
WINDOW	*init_score(t_visu *visu);
void    visu_run(t_vm vm, WINDOW *win, t_visu *visu, WINDOW *score);
void	init_pairy_print_header(WINDOW *score, WINDOW *win);
void    print_score(t_visu *visu, WINDOW *score, t_vm vm, WINDOW *win);
t_visu *inti_visu(void);

//run.c
int 					run(t_vm *vm);

//free.c
t_vm					*free_vm(t_vm *vm);
t_champ					*rec_free_champs(t_champ *champs);
int						free_visu(t_visu *visu);

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
int						check_num(t_champ *ch, int num);

//getters.c
t_champ					*get_champ_by_num(t_champ *list, int num);

//process.c
int						add_process(t_vm *vm, int pc, int id);
void					check_process(t_vm *vm);

//option.c
int						opt(char **av, int ac, int *i, t_vm *vm);

//init_tools.c
int						known_opt(char *opt);
int						check_inputs(void);
int						list_length(t_champ *champ);
int						activate_visu(t_vm *vm, int *i, int ac);

//instr_params.c
void					get_params(t_instr *instr);
t_instr					instr_params(t_vm *vm, t_process *process, int opc);
int						continue_process(t_vm *vm, t_process *process);

//instr_params_checks.c
int						compare_params(t_param *params, int opcode);

//instructions.c
int						continue_process(t_vm *vm, t_process *process);
int 					type_to_size(int type, int oct);
int						byte_to_int(unsigned char *map, int cursor,
						int amount_of_bytes);
int						int_to_bytes(int n, int cursor,
						unsigned char *map, t_instr instr);
int						free_params(t_instr instr, int ret);
int						convert_params(t_instr *instr, int limit);
int						convert_params_unrestrained(t_instr *instr, int limit);
int						decal_pc(t_instr instr, int decal, int ret);
int						convert_params_start(t_instr *instr, int start,
						int limit);
int						valid_reg(int reg);
int						get_address(int value);
int						live(t_instr instr);
int						ld(t_instr instr);
int						st(t_instr instr);
int						add(t_instr instr);
int						sub(t_instr instr);
int						and(t_instr instr);
int						or(t_instr instr);
int						xor(t_instr instr);
int						zjmp(t_instr instr);
int						ldi(t_instr instr);
int						sti(t_instr instr);
int						core_fork(t_instr instr);
int						lld(t_instr instr);
int						lldi(t_instr instr);
int						core_lfork(t_instr instr);
int						aff(t_instr instr);

#endif
