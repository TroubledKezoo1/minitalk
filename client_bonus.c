/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:37:53 by ulyildiz          #+#    #+#             */
/*   Updated: 2023/12/29 19:28:43 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	check_and_convert_pid(char *pid)
{
	pid_t	res;
	int		i;

	i = 0;
	while (pid[i] != '\0')
	{
		if (!('0' <= pid[i] && pid[i] <= '9'))
		{
			write(1, "Server's PID have to contain only numbers.\n", 42);
			exit(1);
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
		write(1, "Connection lost.", 16);
		exit(1);
	}
	i = 0;
	while (i < 8)
	{
		if ((letter & (1 << i)) != 0)
			kill(*pid, SIGUSR1);
		else
			kill(*pid, SIGUSR2);
		usleep(150);
		i++;
	}
}

void	c_pid_send(int *pid)
{
	pid_t	c_pid;
	int		i;

	c_pid = getpid();
	i = 0;
	while (i < 32)
	{
		if ((c_pid & (1 << i)) != 0)
			kill(*pid, SIGUSR1);
		else
			kill(*pid, SIGUSR2);
		i++;
		usleep(150);
	}
}

void	f_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		write(1, "Message is complated\n", 21);
		exit(0);
	}
}

int	main(int argc, char *argv[])
{
	pid_t	pid;
	int		i;

	signal(SIGUSR1, f_handler);
	if (argc != 3)
	{
		write(1, "Type as:./client <server_pid_number> <string>\n", 46);
		return (1);
	}
	i = 0;
	pid = check_and_convert_pid(argv[1]);
	if (kill(pid, 0) != 0)
	{
		write(1, "Invalid PID.\n", 12);
		exit(1);
	}
	c_pid_send(&pid);
	while (argv[2][i] != '\0')
		send_byte(argv[2][i++], &pid);
	send_byte('\n', &pid);
	send_byte('\0', &pid);
	return (0);
}
