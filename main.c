#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "libft/libft.h"

char	put_error(const char *error)
{
	write(2, "error: ", 7);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	exit(1);
}

int		redirect_in(const char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{	
		put_error(file);
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
		put_error(file);
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

int		main(int argc, char *argv[])
{
	int		pipefd[2];
	pid_t	pid;

	pipe(pipefd);
	pid = fork();
	if (pid > 0)
	{
		redirect_out(argv[2]);
		connect_pipe(pipefd, STDIN_FILENO);
		execve("/bin/cat", STDOUT_FILENO, 0);
	}
	else if (pid == 0) // child process
	{
		redirect_in(argv[1]);
		connect_pipe(pipefd, STDIN_FILENO);
		execve("/bin/cat", STDOUT_FILENO, 0);
	}
	return (0);
}

redirect_in(argv[1]);
	execve("/bin/cat", STDOUT_FILENO, 0);
	redirect_out(argv[2]);