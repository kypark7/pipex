#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "libft/libft.h"
#include "pipex.h"

extern char **environ;

int		redirect_in(const char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{	
		perror(file);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int		redirect_out(const char *file)
{
	int fd;

	fd = open(file, O_RDWR | O_CREAT, 0644);
	if (fd < 0)
	{
		perror(file);
		return(-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static void connect_pipe(int pipefd[2], int io)
{
	dup2(pipefd[io], io);
	close(pipefd[0]);
	close(pipefd[1]);
}

static void	cmd_init(const char *cmd, t_cmd *strt)
{
	char	**chunk;

	chunk = ft_split(cmd, ' ');
	strt->cmd[0] = ft_strjoin("/bin/", chunk[0]);
	strt->cmd[1] = ft_strjoin("/usr/local/bin/", chunk[0]);
	strt->cmd[2] = ft_strjoin("/usr/bin/", chunk[0]);
	strt->cmd[3] = ft_strjoin("/usr/sbin/", chunk[0]);
	strt->cmd[4] = ft_strjoin("/sbin/", chunk[0]);
	strt->argv = (char *const *)chunk;
}

static void	run_cmd(const char *cmd, t_cmd *cmd_arg)
{
	int i;

	i = 0;
	cmd_init(cmd, cmd_arg);
	while(i < 5)
		execve(cmd_arg->cmd[i++], cmd_arg->argv, environ);
	perror(cmd_arg->argv[0]);
}

int		main(int argc, char *argv[])
{
	int		pipefd[2];
	pid_t	pid;
	t_cmd	cmd;

	pipe(pipefd);
	pid = fork();
	if (pid > 0)
{
		redirect_out(FILE_2);
		connect_pipe(pipefd, STDIN_FILENO);
		run_cmd(CMD_2, &cmd);
	}
	else if (pid == CHILD)
	{
		redirect_in(FILE_1);
		connect_pipe(pipefd, STDOUT_FILENO);
		run_cmd(CMD_1, &cmd);
	}
	return (0);
}
