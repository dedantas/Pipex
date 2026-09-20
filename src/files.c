/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:46:42 by dedantas          #+#    #+#             */
/*   Updated: 2025/10/21 00:46:58 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_input_file(char *filename, t_pipex *pipex)
{
	int	fd;
	int	fd_null;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		print_file_error(filename);
		fd_null = open("/dev/null", O_RDONLY);
		if (fd_null == -1)
			cleanup_exit(pipex, EXIT_FAILURE);
		dup2(fd_null, STDIN_FILENO);
		close(fd_null);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	open_output_file(char *filename, t_pipex *pipex)
{
	int	fd;

	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
	{
		print_file_error(filename);
		cleanup_exit(pipex, EXIT_FAILURE);
	}
	return (fd);
}

int	wait_for_children(pid_t last_pid)
{
	pid_t	pid;
	int		status;
	int		last_status;

	last_status = 0;
	pid = 1;
	while (pid > 0)
	{
		pid = wait(&status);
		if (pid == last_pid && WIFEXITED(status))
			last_status = WEXITSTATUS(status);
	}
	return (last_status);
}
