/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kypark <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 21:26:57 by kypark            #+#    #+#             */
/*   Updated: 2021/06/11 21:26:59 by kypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void		redirect_in(const char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void		redirect_out(const char *file)
{
	int		fd;

	fd = open(file, O_RDWR | O_CREAT, 0644);
	if (fd < 0)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	connect_pipe(int pipefd[2], int io)
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

static void	run_cmd(const char *cmd)
{
	int		i;
	t_cmd	cmd_;

	i = 0;
	cmd_init(cmd, &cmd_);
	while (i < 5)
		execve(cmd_.cmd[i++], cmd_.argv, NULL);
	perror(cmd_.argv[0]);
}

int			main(int argc, char *argv[])
{
	int		pipefd[2];
	int		status;
	pid_t	pid;

	if (argc != 5)
		return (0);
	pipe(pipefd);
	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) == 0)
			exit(1);
		redirect_out(argv[4]);
		connect_pipe(pipefd, STDIN_FILENO);
		run_cmd(argv[3]);
	}
	else if (pid == CHILD)
	{
		redirect_in(argv[1]);
		connect_pipe(pipefd, STDOUT_FILENO);
		run_cmd(argv[2]);
	}
	return (0);
}
