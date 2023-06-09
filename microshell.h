/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasha <sasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:56:02 by hsliu             #+#    #+#             */
/*   Updated: 2023/05/01 21:09:48 by sasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>

int		ft_strlen(char *s);
int		cd(char **args, int fd[2]);

char	**ft_get_args(int i, char **argv);
void	ft_set_pipe(int i, char **argv, int cmd, int fd[6]);
void	ft_close_fd(int fd[2]);
void	ft_close_std(void);

void	ft_child_exec(int i, char **argv, int fd[2]);
void	ft_parent(int fd[2]);

int		ft_is_first(int i, char **argv);
int		ft_is_last(int i, char **argv);

int		ft_increment_i(int i, char **argv);
int		ft_increment_cmd(int i, char **argv, int cmd);

#endif