#ifndef GET_CMDS_H
# define GET_CMDS_H
# include <stdlib.h>

typedef struct	S_cmdli
{
	char			*cmd_path;
	char			**cmd_args;
	int				**pipe_in;
	int				**pipe_out;
	int				fd_in;
	int				fd_out;
	int				and_or;
	struct S_cmdli	*previous;
	struct S_cmdli	*next;
}					t_cmdli;

#endif
