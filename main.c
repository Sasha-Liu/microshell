/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasha <sasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:59:32 by hsliu             #+#    #+#             */
/*   Updated: 2023/05/01 15:57:23 by sasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int	main(int argc, char **argv)
{
	int		i;
	int		fd[4];
	int		pid;
	char	**args;
	
	if (argc == 1)
	{
		return (0);
	}
	if (strcmp("cd", argv[1]) == 0)
	{
		exit(cd(argc - 1, argv + 1));
	}
	i = 1;
	//pipe(fd);
	while (argv[i])
	{
		args = ft_get_args(i, argv);
		if (!args)
			exit(1);
		pipe(fd + (i % 2) * 2);
		pid = fork();
		if (pid == 0)
		{
			ft_child_exec(i, argv, args, fd);
		}
		else
		{
			//wait for the child to terminate
			//augument i 
			//read from pipe
			dup2(fd[0], 0);
			//write to pipe or stdout
			
		}
		i++;
	}
	
	
}
