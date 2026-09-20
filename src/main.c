/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:44:23 by dedantas          #+#    #+#             */
/*   Updated: 2025/11/10 17:12:43 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_pipex(t_pipex *pipex)
{
	pipex->input_fd = -1;
	pipex->output_fd = -1;
	pipex->here_doc = 0;
	pipex->limiter = NULL;
	pipex->last_pid = -1;
	pipex->exit_status = 0;
}

static pid_t	create_child_process(char *cmd, char *envp[], int is_last)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		error_exit("pipex: pipe error", NULL, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		error_exit("pipex: fork error", NULL, EXIT_FAILURE);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (!is_last)
			dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execute_cmd(cmd, envp);
	}
	close(pipe_fd[1]);
	if (!is_last)
		dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (pid);
}

static void	execute_commands(int argc, char *argv[],
		char *envp[], t_pipex *pipex)
{
	create_child_process(argv[2], envp, 0);
	dup2(pipex->output_fd, STDOUT_FILENO);
	close(pipex->output_fd);
	pipex->last_pid = create_child_process(argv[argc - 2], envp, 1);
	pipex->exit_status = wait_for_children(pipex->last_pid);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc == 5)
	{
		init_pipex(&pipex);
		pipex.input_fd = open_input_file(argv[1], &pipex);
		pipex.output_fd = open_output_file(argv[argc - 1], &pipex);
		execute_commands(argc, argv, envp, &pipex);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		return (pipex.exit_status);
	}
	ft_putstr_fd(USAGE_MSG, 2);
	exit(EXIT_FAILURE);
}
