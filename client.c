/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:41:33 by ysarac            #+#    #+#             */
/*   Updated: 2023/12/29 19:10:25 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	check_and_convert_pid(char *pid)
{
	unsigned int	res;
	int				i;

	i = 0;
	while (pid[i] != '\0')
	{
		if (!('0' <= pid[i] && pid[i] <= '9'))
		{
			write (1, "Server's PID have to contain only numbers.\n", 42);
			exit (1);
		}
		i++;
	}
	res = 0;
	while (*pid != '\0')
		res = (res * 10) + (*(pid++) - '0');
	return (res);
}

void	send_byte(char letter, pid_t *pid)
{
	int	i;

	if (kill(*pid, 0) != 0)
	{
		write (1, "Connection lost.", 16);
		exit(1);
	}
	i = 0;
	while (i < 8)
	{
		if ((letter & (1 << i)) != 0)
			kill(*pid, SIGUSR1);
		else
			kill(*pid, SIGUSR2);
		usleep(200);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	pid_t	pid;
	size_t	i;

	if (argc != 3)
	{
		write (1, "Type as:./client <server_pid_number> <string>\n", 46);
		return (1);
	}
	i = 0;
	pid = check_and_convert_pid(argv[1]);
	if (kill(pid, 0) != 0)
	{
		write (1, "Invalid PID.\n", 12);
		exit(1);
	}
	while (argv[2][i] != '\0')
		send_byte(argv[2][i++], &pid);
	send_byte('\n', &pid);
	return (0);
}
