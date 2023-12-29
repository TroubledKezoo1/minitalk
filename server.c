/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:50:04 by ysarac            #+#    #+#             */
/*   Updated: 2023/12/29 19:25:31 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_pid(pid_t pid)
{
	if (pid >= 10)
		print_pid(pid / 10);
	write (1, &"0123456789"[pid % 10], 1);
}

void	handler(int signal)
{
	static int	i;
	static char	c;

	if (signal == SIGUSR1)
		c |= (1 << i);
	i++;
	if (i == 8)
	{
		write (1, &c, 1);
		i = 0;
		c = 0;
	}
}

int	main(int argc, char *argv[])
{
	pid_t	pid;

	(void)argv;
	if (argc == 1)
	{
		write (1, "Server PID: ", 12);
		print_pid(pid = getpid());
		write(1, "\n", 1);
		signal(SIGUSR1, handler);
		signal(SIGUSR2, handler);
		while (1)
			pause();
	}
	else
	{
		write (1, "Please, just type \"./server\".", 28);
		return (1);
	}
	return (0);
}
