/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:46:09 by dedantas          #+#    #+#             */
/*   Updated: 2025/10/21 00:46:26 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**extract_paths(char *envp[])
{
	char	**paths;
	char	*env_path;

	paths = NULL;
	env_path = NULL;
	while (*envp && !env_path)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			env_path = *envp + 5;
		envp++;
	}
	if (env_path)
		paths = ft_split(env_path, ':');
	return (paths);
}

static char	*find_cmd_path(char *cmd, char *envp[])
{
	char	**paths;
	char	*full_path;
	char	*path_slash;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = extract_paths(envp);
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		path_slash = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path_slash, cmd);
		free(path_slash);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_split(paths), full_path);
		free(full_path);
	}
	free_split(paths);
	return (NULL);
}

void	execute_cmd(char *cmd, char *envp[])
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args || !cmd_args[0])
		error_exit("pipex: command not found", NULL, 127);
	cmd_path = find_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		ft_putstr_fd(CMD_NOT_FOUND, 2);
		ft_putstr_fd(cmd_args[0], 2);
		ft_putchar_fd('\n', 2);
		free_split(cmd_args);
		exit(127);
	}
	if (execve(cmd_path, cmd_args, envp) == -1)
		handle_exec_error(cmd_args, cmd_path);
}
