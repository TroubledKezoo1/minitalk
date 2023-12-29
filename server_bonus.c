/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:52:03 by ysarac            #+#    #+#             */
/*   Updated: 2023/12/29 19:28:08 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	print_pid(pid_t pid)
{
	if (pid >= 10)
		print_pid(pid / 10);
	write(1, &"0123456789"[pid % 10], 1);
}

pid_t	nbdsk(int flag, pid_t c_pid, int signal)
{
	if (signal == SIGUSR1)
		c_pid |= (1 << flag);
	return (c_pid);
}

int	clearflags(pid_t c_pid, int *flag)
{
	kill(c_pid, SIGUSR1);
	*flag = 0;
	return (0);
}

void	handler(int signal)
{
	static int		i;
	static char		c;
	static int		flag;
	static pid_t	c_pid;

	if (flag < 32)
	{
		c_pid = nbdsk(flag, c_pid, signal);
		flag++;
	}
	else
	{
		if (signal == SIGUSR1)
			c |= (1 << i);
		if (++i == 8)
		{
			write(1, &c, 1);
			if (c == '\0')
				c_pid = clearflags(c_pid, &flag);
			i = 0;
			c = 0;
		}
	}
}

int	main(int argc, char *argv[])
{
	pid_t	pid;

	(void)argv;
	if (argc == 1)
	{
		write(1, "Server PID: ", 12);
		print_pid(pid = getpid());
		write(1, "\n", 1);
		signal(SIGUSR1, handler);
		signal(SIGUSR2, handler);
		while (1)
			pause();
	}
	else
	{
		write(1, "Please, just type \"./server\".", 28);
		return (1);
	}
	return (0);
}
