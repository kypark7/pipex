#ifndef PIPEX_H

# define PIPEX_H
# define CHILD 0
# define FILE_1	argv[1]
# define FILE_2	argv[4]
# define CMD_1	argv[2]
# define CMD_2	argv[3]



typedef struct	s_cmd
{
	const char	**cmd;
	char * const *argv;
	char * const *envp;
}				t_cmd;




#endif