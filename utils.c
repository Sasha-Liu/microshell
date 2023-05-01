/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasha <sasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:36:35 by sasha             #+#    #+#             */
/*   Updated: 2023/05/01 15:44:23 by sasha            ###   ########.fr       */
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

void	ft_increment_i(int *i, char **argv)
{
	while (argv[*i] && strcmp("|", argv[*i]) && strcmp(";", argv[*i]))
	{
		*i++;
	}
	if (!(argv[*i]))
		return ;
	(*i)++;
}

void	ft_child_exec(int i, char **argv, char **args, int fd[2])
{
	extern char	**environ;
	
	//if is the first cmd or preceded by ;
	if (i == 1 || !strcmp(";", argv[i - 1]))
		;
	else
		dup2(fd[0], 0);
	dup2(fd[1], 1);
	execve(args[1], args, environ);
	write(2, "error: cannot execute ", 22);
	write(2, args[0], ft_strlen(args[0]));
	write(2, "\n", 1);
	exit(1);
}

/*
	increment i, free resource
*/
void	ft_parent(int i, char **argv, char **args, int fd[2])
{
	int	status;
	//int	temp[2];
	
	if (i == 1 || !strcmp(";", argv[i - 1]))
		close(fd[0]);
	
	close(fd[1]);
	waitpid(-1, &status, 0);
	//pipe(temp);
	//read from pipe (store where ?)
	
	//close read end
	//reopen pipe
	//write into pipe or stdout
}