/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:42:14 by dedantas          #+#    #+#             */
/*   Updated: 2025/10/21 00:43:49 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include "libft.h"

// Error messages
# define CMD_NOT_FOUND "pipex: command not found: "
# define USAGE_MSG "Usage: infile \"cmd1\" \"cmd2\" outfile\n"
# define USAGE_HD_MSG "Usage: here_doc LIMITER \"cmd1\" \"cmd2\" outfile\n"

// Structs
typedef struct s_pipex
{
	int		input_fd;
	int		output_fd;
	int		here_doc;
	char	*limiter;
	pid_t	last_pid;
	int		exit_status;
}	t_pipex;

// Function prototypes
void	execute_cmd(char *cmd, char *envp[]);
void	free_split(char **arr);
int		open_input_file(char *filename, t_pipex *pipex);
int		open_output_file(char *filename, t_pipex *pipex);
void	handle_here_doc(t_pipex *pipex);
int		wait_for_children(pid_t last_pid);
void	cleanup_exit(t_pipex *pipex, int exit_code);
void	error_exit(char *msg, char *arg, int exit_code);
void	handle_exec_error(char **cmd_args, char *cmd_path);
void	print_file_error(char *filename);

#endif
