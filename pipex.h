/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kypark <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 21:27:23 by kypark            #+#    #+#             */
/*   Updated: 2021/06/11 21:27:25 by kypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
# define CHILD 0

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# include "libft/libft.h"

typedef struct		s_cmd
{
	const char		**cmd;
	char * const	*argv;
	char * const	*envp;
}					t_cmd;

int					main(int argc, char *argv[]);

static void			run_cmd(const char *cmd);
static void			cmd_init(const char *cmd, t_cmd *strt);

static void			connect_pipe(int pipefd[2], int io);

void				redirect_in(const char *file);
void				redirect_out(const char *file);

#endif
