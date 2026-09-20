/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:44:23 by dedantas          #+#    #+#             */
/*   Updated: 2025/11/10 17:12:15 by dedantas         ###   ########.fr       */
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

static void	here_doc(t_pipex *pipex)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
		error_exit("pipex: pipe error", NULL, EXIT_FAILURE);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strlen(line) == ft_strlen(pipex->limiter) + 1
			&& !ft_strncmp(line, pipex->limiter, ft_strlen(pipex->limiter))
			&& line[ft_strlen(pipex->limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
}

static void	execute_commands(int argc, char *argv[],
		char *envp[], t_pipex *pipex)
{
	int	i;

	i = 2 + pipex->here_doc;
	while (i < argc - 2)
		create_child_process(argv[i++], envp, 0);
	dup2(pipex->output_fd, STDOUT_FILENO);
	close(pipex->output_fd);
	pipex->last_pid = create_child_process(argv[argc - 2], envp, 1);
	pipex->exit_status = wait_for_children(pipex->last_pid);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc > 4)
	{
		init_pipex(&pipex);
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			if (argc < 6)
			{
				ft_putstr_fd(USAGE_HD_MSG, 2);
				exit(EXIT_FAILURE);
			}
			pipex.here_doc = 1;
			pipex.limiter = argv[2];
			here_doc(&pipex);
		}
		else
			pipex.input_fd = open_input_file(argv[1], &pipex);
		pipex.output_fd = open_output_file(argv[argc - 1], &pipex);
		execute_commands(argc, argv, envp, &pipex);
		return (pipex.exit_status);
	}
	ft_putstr_fd(USAGE_HD_MSG, 2);
	exit(EXIT_FAILURE);
}
