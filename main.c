/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasha <sasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:59:32 by hsliu             #+#    #+#             */
/*   Updated: 2023/05/01 19:34:55 by sasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int	main(int argc, char **argv)
{
	int		i;
	int		fd[6];
	int		pid;
	int		cmd;
	
	if (argc == 1)
	{
		return (0);
	}
	if (strcmp("cd", argv[1]) == 0)
	{
		exit(cd(argc - 1, argv + 1));
	}
	//one single cmd
	i = 1;
	cmd = 0;
	ft_exec_one(i, argv);
	while (argv[i])
	{
		ft_set_pipe(i, argv, cmd, fd);
		pid = fork();
		if (pid == 0)
		{
			ft_child_exec(i, argv, fd);
		}
		else
		{
			ft_parent(fd);
		}
		i = ft_increment_i(i, argv);
		cmd++;
	}
}
