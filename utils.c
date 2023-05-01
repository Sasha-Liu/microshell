/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasha <sasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:36:35 by sasha             #+#    #+#             */
/*   Updated: 2023/05/01 20:19:13 by sasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

int	cd(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "error: cd: bad arguments\n", 25);
		return (1);
	}
	if (chdir(argv[1]))
	{
		write(2, "error: cd: cannot change directory to ", 38);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, "\n", 1);
		return (1);
	}
	return (0);
}

/* 
	return a char ** for execve to use as argument
*/
char	**ft_get_args(int i, char **argv)
{
	char	**p;
	int		count;

	count = 0;
	while (argv[i] && strcmp("|", argv[i]) && strcmp(";", argv[i]))
	{
		i++;
		count++;
	}
	p = malloc(sizeof(char *) * (count + 1));
	if (!p)
	{
		return (NULL);
	}
	p[count] = NULL;
	while (count > 0)
	{
		count--;
		i--;
		p[count] = argv[i];
	}
	return (p);
}

int	ft_increment_i(int i, char **argv)
{
	while (argv[i] && strcmp("|", argv[i]) && strcmp(";", argv[i]))
		i++;
	if (argv[i])
		i++;
	return (i);
}

void	ft_child_exec(int i, char **argv, int fd[2])
{
	extern char	**environ;
	char		**args;
	
	args = ft_get_args(i, argv);
	if (!args)
	{
		ft_close_fd(fd);
		exit(1);
	}
	//ft_print_args(args);
	if (fd[0] != 0)
		dup2(fd[0], 0);
	if (fd[1] != 1)
		dup2(fd[1], 1);
	execve(args[0], args, environ);
	write(2, "error: cannot execute ", 22);
	write(2, args[0], ft_strlen(args[0]));
	write(2, "\n", 1);
	ft_close_fd(fd);
	free(args);
	exit(1);
}

/*
	increment i, free resource
*/
void	ft_parent(int fd[2])
{
	int	status;
	
	ft_close_fd(fd);
	waitpid(-1, &status, 0);
}

void	ft_set_pipe(int i, char **argv, int cmd, int fd[6])
{
	if (ft_is_last(i, argv))
	{
		fd[1] = 1;
		if (cmd % 2)
		{
			fd[0] = dup(fd[2]);
			close(fd[2]);
		}
		else
		{
			fd[0] = dup(fd[4]);
			close(fd[4]);
		}
	}
	else if (ft_is_first(i, argv))
	{
		pipe(fd + 2);
		fd[0] = 0;
		fd[1] = dup(fd[3]);
		close(fd[3]);
	}
	else if (cmd % 2)
	{
		pipe(fd + 4);
		fd[0] = dup(fd[2]);
		fd[1] = dup(fd[5]);
		close(fd[2]);
		close(fd[5]);
	}
	else
	{
		pipe(fd + 2);
		fd[0] = dup(fd[4]);
		fd[1] = dup(fd[3]);
		close(fd[4]);
		close(fd[3]);
	}
	
}

int	ft_is_first(int i, char **argv)
{
	if (i == 1)
		return (1);
	if (strcmp(";", argv[i - 1]) == 0)
		return (1);
	return (0);
}

int	ft_is_last(int i, char **argv)
{
	while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
	{
		i++;
	}
	if (argv[i] == NULL)
		return (1);
	if (strcmp(argv[i], ";") == 0)
		return (1);
	return (0);
}

void	ft_close_fd(int fd[2])
{
	if (fd[0] != 0)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
}

/*
	exec the cmd if its the only one
*/
void	ft_exec_one(int i, char **argv)
{
	char		**args;
	extern char	**environ;
	
	if (!ft_is_first(i, argv) || !ft_is_last(i, argv))
		return ;
	args = ft_get_args(i, argv);
	if (!args)
		exit(1);
	execve(args[0], args, environ);
	write(2, "error: cannot execute ", 22);
	write(2, args[0], ft_strlen(args[0]));
	write(2, "\n", 1);
	free(args);
	exit(0);
}