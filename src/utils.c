/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:47:15 by dedantas          #+#    #+#             */
/*   Updated: 2025/10/21 00:47:39 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	error_exit(char *msg, char *arg, int exit_code)
{
	ft_putstr_fd(msg, 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	ft_putchar_fd('\n', 2);
	exit(exit_code);
}

void	print_file_error(char *filename)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(filename, 2);
	ft_putchar_fd('\n', 2);
}

void	cleanup_exit(t_pipex *pipex, int exit_code)
{
	if (pipex->input_fd != -1)
		close(pipex->input_fd);
	if (pipex->output_fd != -1)
		close(pipex->output_fd);
	exit(exit_code);
}

void	handle_exec_error(char **cmd_args, char *cmd_path)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd(CMD_NOT_FOUND, 2);
		ft_putstr_fd(cmd_args[0], 2);
		ft_putchar_fd('\n', 2);
	}
	else
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd_args[0], 2);
		ft_putchar_fd('\n', 2);
	}
	free(cmd_path);
	free_split(cmd_args);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}
